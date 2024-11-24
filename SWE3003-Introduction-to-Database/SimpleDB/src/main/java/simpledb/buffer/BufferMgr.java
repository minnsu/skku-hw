package simpledb.buffer;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

import simpledb.file.*;
import simpledb.log.LogMgr;

/**
 * Manages the pinning and unpinning of buffers to blocks.
 * @author Edward Sciore
 *
 */
public class BufferMgr {
   private ArrayList<Buffer> unpinned;
   private HashMap<BlockId, Buffer> buffers; /* buffer pool */ 
   private int numAvailable;   /* the number of available (unpinned) buffer slots */
   private static final long MAX_TIME = 1000; /* 10 seconds */
   private FileMgr fm;
   private LogMgr lm;
   private int numbuffs;
   private int buffcount = 0;

   /**
    * Constructor:  Creates a buffer manager having the specified 
    * number of buffer slots.
    * This constructor depends on a {@link FileMgr} and
    * {@link simpledb.log.LogMgr LogMgr} object.
    * @param numbuffs the number of buffer slots to allocate
    */
   public BufferMgr(FileMgr fm, LogMgr lm, int numbuffs) {
      unpinned = new ArrayList<Buffer>();
      buffers = new HashMap<BlockId, Buffer>();
      numAvailable = numbuffs;
      this.fm = fm;
      this.lm = lm;
      this.numbuffs = numbuffs;
   }
   
   /**
    * Returns the number of available (i.e. unpinned) buffers.
    * @return the number of available buffers
    */
   public synchronized int available() {
      return numAvailable;
   }
   
   /**
    * Flushes the dirty buffers modified by the specified transaction.
    * @param txnum the transaction's id number
    */
   public synchronized void flushAll(int txnum) {
      for (Map.Entry<BlockId, Buffer> entry : buffers.entrySet()){
         Buffer buff = entry.getValue();
         if (buff.modifyingTx() == txnum)
            buff.flush();
      }
   }
   
   /**
    * Unpins the specified data buffer. If its pin count
    * goes to zero, then notify any waiting threads.
    * @param buff the buffer to be unpinned
    */
   public synchronized void unpin(Buffer buff) {
      buff.unpin();
      if (!buff.isPinned()) {
         unpinned.add(buff);

         numAvailable++;
         notifyAll();
      }
   }
   
   /**
    * Pins a buffer to the specified block, potentially
    * waiting until a buffer becomes available.
    * If no buffer becomes available within a fixed 
    * time period, then a {@link BufferAbortException} is thrown.
    * @param blk a reference to a disk block
    * @return the buffer pinned to that block
    */
   public synchronized Buffer pin(BlockId blk) {
      try {
         long timestamp = System.currentTimeMillis();
         Buffer buff = tryToPin(blk);
         while (buff == null && !waitingTooLong(timestamp)) {
            wait(MAX_TIME);
            buff = tryToPin(blk);
         }
         if (buff == null)
            throw new BufferAbortException();
         return buff;
      }
      catch(InterruptedException e) {
         throw new BufferAbortException();
      }
   }  
   
   /**
    * Returns true if starttime is older than 10 seconds
    * @param starttime timestamp 
    * @return true if waited for more than 10 seconds
    */
   private boolean waitingTooLong(long starttime) {
      return System.currentTimeMillis() - starttime > MAX_TIME;
   }
   
   /**
    * Tries to pin a buffer to the specified block. 
    * If there is already a buffer assigned to that block
    * then that buffer is used;  
    * otherwise, an unpinned buffer from the pool is chosen.
    * Returns a null value if there are no available buffers.
    * @param blk a reference to a disk block
    * @return the pinned buffer
    */
   private Buffer tryToPin(BlockId blk) {
      Buffer buff = findExistingBuffer(blk);
      if (buff == null) {
         buff = chooseUnpinnedBuffer(blk);
         if (buff == null)
            return null;
         buffers.remove(buff.block());
         buff.assignToBlock(blk);
         buffers.put(blk, buff);
      }
      if (!buff.isPinned())
         numAvailable--;
      buff.pin();
      return buff;
   }
   
   /**
    * Find and return a buffer assigned to the specified block. 
    * @param blk a reference to a disk block
    * @return the found buffer       
    */
   private Buffer findExistingBuffer(BlockId blk) {
      Buffer buff = buffers.get(blk);
      if(buff != null){
         if(!buff.isPinned()){
            unpinned.remove(buff);
         }
         return buff;
      }
      return null;
      // for (Buffer buff : bufferpool) {
      //    BlockId b = buff.block();
      //    if (b != null && b.equals(blk))
      //       return buff;
      // }
      // return null;
   }
   
   /**
    * Find and return an unpinned buffer     . 
    * @return the unpinned buffer       
    */
   private Buffer chooseUnpinnedBuffer(BlockId blk) {
      if(buffers.size() < numbuffs){
         Buffer buff = new Buffer(this.fm, this.lm, this.buffcount++);
         buffers.put(blk, buff);
         return buff;
      }
      while(!unpinned.isEmpty() && unpinned.get(0).isPinned()){
         unpinned.remove(0);
      }
      if(!unpinned.isEmpty()){
         return unpinned.remove(0);
      }
      return null;
      // for (Buffer buff : bufferpool)
      //    if (!buff.isPinned())
      //    return buff;
      // return null;
   }

   public void printStatus() {
      System.out.println("Allocated Buffers:");
      for(Map.Entry<BlockId, Buffer> entry : buffers.entrySet()){
         System.out.println("Buffer " + entry.getValue().getId() + ": " + entry.getKey().toString() + " " + (entry.getValue().isPinned() ? "pinned" : "unpinned"));
      }
      System.out.print("Unpinned Buffers in LRU order:");
      for(Buffer buff : unpinned){
         System.out.print(" " + buff.getId());
      }
      System.out.println();
   }
}
