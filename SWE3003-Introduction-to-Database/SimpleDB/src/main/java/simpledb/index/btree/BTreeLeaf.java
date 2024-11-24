package simpledb.index.btree;

import simpledb.file.BlockId;
import simpledb.tx.Transaction;
import simpledb.record.*;
import simpledb.query.Constant;

/**
 * An object that holds the contents of a B-tree leaf block.
 * @author Edward Sciore
 */
public class BTreeLeaf {
   private Transaction tx;
   private Layout layout;
   private Constant searchkey;
   private BTPage contents;
   private int currentslot;
   private String filename;
   public int blknum;

   /**
    * Opens a buffer to hold the specified leaf block.
    * The buffer is positioned immediately before the first record
    * having the specified search key (if any).
    * @param blk a reference to the disk block
    * @param layout the metadata of the B-tree leaf file
    * @param searchkey the search key value
    * @param tx the calling transaction
    */
   public BTreeLeaf(Transaction tx, BlockId blk, Layout layout, Constant searchkey) {
      this.tx = tx;
      this.layout = layout;
      this.searchkey = searchkey;
      this.blknum = blk.number();
      contents = new BTPage(tx, blk, layout);
      currentslot = contents.findSlotBefore(searchkey);
      filename = blk.fileName();            
   }

   /**
    * Closes the leaf page.
    */
   public void close() {
      contents.close();
   }

   /**
    * Moves to the next leaf record having the 
    * previously-specified search key.
    * Returns false if there is no more such records.
    * @return false if there are no more leaf records for the search key
    */
   public boolean next() {
      currentslot++;
      if (currentslot >= contents.getNumRecs()) 
         return tryOverflow();
      else if (contents.getDataVal(currentslot).equals(searchkey))
         return true;
      else 
         return tryOverflow();
   }

   /**
    * Returns the dataRID value of the current leaf record.
    * @return the dataRID of the current record
    */
   public RID getDataRid() {
      return contents.getDataRid(currentslot);
   }

   /**
    * Deletes the leaf record having the specified dataRID
    * @param datarid the dataRId whose record is to be deleted
    */
   public void delete(RID datarid) {
      while(next())
         if(getDataRid().equals(datarid)) {
            contents.delete(currentslot);
            return;
         }
   }

   /**
    * Inserts a new leaf record having the specified dataRID
    * and the previously-specified search key.
    * If the record does not fit in the page, then 
    * the page splits and the method returns the
    * directory entry for the new page;
    * otherwise, the method returns null.  
    * If all of the records in the page have the same dataval,
    * then the block does not split; instead, all but one of the
    * records are placed into an overflow block.
    * @param datarid the dataRID value of the new record
    * @return the directory entry of the newly-split page, if one exists.
    */
   public DirEntry insert(RID datarid, BTreeLeaf left, BTreeLeaf right, BTreeDir parent) {
      redistribution(left, right, parent);
      if (contents.getFlag() >= 0 && contents.getDataVal(0).compareTo(searchkey) > 0) {
         Constant firstval = contents.getDataVal(0);
         BlockId newblk = contents.split(0, contents.getFlag());
         currentslot = 0;
         contents.setFlag(-1);
         contents.insertLeaf(currentslot, searchkey, datarid); 
         return new DirEntry(firstval, newblk.number());  
      }
      
      currentslot++;
      contents.insertLeaf(currentslot, searchkey, datarid);
      if (!contents.isFull())
         return null;
      // else page is full, so split it
      Constant firstkey = contents.getDataVal(0);
      Constant lastkey  = contents.getDataVal(contents.getNumRecs()-1);
      if (lastkey.equals(firstkey)) {
         // create an overflow block to hold all but the first record
         BlockId newblk = contents.split(1, contents.getFlag());
         contents.setFlag(newblk.number());
         return null;
      }
      else {
         int splitpos = contents.getNumRecs() / 2;
         Constant splitkey = contents.getDataVal(splitpos);
         if (splitkey.equals(firstkey)) {
            // move right, looking for the next key
            while (contents.getDataVal(splitpos).equals(splitkey))
               splitpos++;
            splitkey = contents.getDataVal(splitpos);
         }
         else {
            // move left, looking for first entry having that key
            while (contents.getDataVal(splitpos-1).equals(splitkey))
               splitpos--;
         }
         BlockId newblk = contents.split(splitpos, -1);
         return new DirEntry(splitkey, newblk.number());
      }
   }

   private boolean tryOverflow() {
      Constant firstkey = contents.getDataVal(0);
      int flag = contents.getFlag();
      if (!searchkey.equals(firstkey) || flag < 0)
         return false;
      contents.close();
      BlockId nextblk = new BlockId(filename, flag);
      contents = new BTPage(tx, nextblk, layout);
      currentslot = 0;
      return true;
   }

   private void redistribution(BTreeLeaf left, BTreeLeaf right, BTreeDir parent) {
      /* 같은 부모를 가진 형제(왼쪽 오른쪽 혹은 어느 한쪽만 있을 수도)에서
       *
       * 한쪽만 있는 경우
       * 왼쪽 > 나 => 왼쪽에서 나로 옮김
       * 왼쪽 < 나 => 나에서 왼쪽으로 옮김
       * 나 < 오른쪽 => 오른쪽에서 나로 옮김
       * 나 > 오른쪽 => 나에서 오른쪽으로 옮김
       * 
       * 두쪽 다 있는 경우
       * 개수 모두 합해서 3등분(평균) 개수로 맞추기
       * 왼쪽 초과 => 나로 이동 => 나 초과 => 오른쪽으로 넘기기
       *                     => 나 미만 => 오른쪽에서 가져오기
       * while(왼쪽 > 평균){
       *    나로 이동;
       *    if(나 > 평균){
       *       while(오른쪽 < 평균){
       *          오른쪽으로 이동;
       *       }
       *    }
       * }
       * while(나 < 평균){
       *    오른쪽에서 가져오기
       * }
       *
       * 왼쪽 미만 => 내가 넘기기 => 나 초과 => 오른쪽으로 넘기기
       *                        => 나 미만 => 오른쪽에서 가져오기
       * while(왼쪽 < 평균){
       *    내가 넘기기;
       *    if(나 == 0){
       *       while(내거 < 평균 - 왼쪽 개수){
       *          오른쪽에서 가져오기;
       *       }
       *    }
       * }
       * while(나 > 평균){
       *    오른쪽으로 넘기기
       * }
       * while(나 < 평균){
       *    오른쪽에서 가져오기
       * }
       * 
      */
      
      // TODO: left, right, this 모두 2/3 이상 사용 중이면? 즉시 반환?

      // System.out.println("Hello!\n");
      int average = 0;
      if(left == null){
         average = (this.contents.getNumRecs() + right.contents.getNumRecs()) / 2;
         if(this.contents.getNumRecs() > average) {
            while(this.contents.getNumRecs() > average){
               // me -> right
               parent.setSlotKey(parent.getRight(), this.contents.getDataVal(this.contents.getNumRecs() - 1), right.blknum);
               this.contents.moveToDest(this.contents.getNumRecs()-1, 0, right.contents);
            }
         } else {
            while(this.contents.getNumRecs() < average){
               // me <- right
               parent.setSlotKey(parent.getRight(), right.contents.getDataVal(1), this.blknum); // 2번째 것이 parent node로 바뀜
               right.contents.moveToDest(0, this.contents.getNumRecs(), this.contents);
            }
         }
         return;
      } else if (right == null){
         average = (this.contents.getNumRecs() + left.contents.getNumRecs()) / 2;
         if(this.contents.getNumRecs() > average) {
            while(this.contents.getNumRecs() > average){
               // left <- me
               parent.setSlotKey(parent.getLeft() + 1, this.contents.getDataVal(1), left.blknum);
               this.contents.moveToDest(0, left.contents.getNumRecs(), left.contents);
            }
         } else {
            while(this.contents.getNumRecs() < average){
               // left -> me
               parent.setSlotKey(parent.getLeft() + 1, left.contents.getDataVal(left.contents.getNumRecs() - 1), this.blknum);
               left.contents.moveToDest(left.contents.getNumRecs()-1, 0, this.contents);
            }
         }
         return;
      }
      // System.out.printf("Hello! %d %d %d\n", left.contents.getNumRecs(), this.contents.getNumRecs(), right.contents.getNumRecs());
      
      average = (left.contents.getNumRecs() + this.contents.getNumRecs() + right.contents.getNumRecs()) / 3;
      if(left.contents.getNumRecs() >= average){
         while(left.contents.getNumRecs() > average){
            // left -> me
            parent.setSlotKey(parent.getLeft() + 1, left.contents.getDataVal(left.contents.getNumRecs() - 1), this.blknum);
            left.contents.moveToDest(left.contents.getNumRecs()-1, 0, this.contents);
            if(this.contents.getNumRecs() > average){
               while(right.contents.getNumRecs() < average){
                  // me -> right
                  parent.setSlotKey(parent.getRight(), this.contents.getDataVal(this.contents.getNumRecs() - 1), right.blknum);
                  this.contents.moveToDest(this.contents.getNumRecs()-1, 0, right.contents);
               }
            }
         }
         while(this.contents.getNumRecs() < average) {
            // me <- right
            parent.setSlotKey(parent.getRight(), right.contents.getDataVal(1), this.blknum);
            right.contents.moveToDest(0, this.contents.getNumRecs(), this.contents);
         }
      } else {
         while(left.contents.getNumRecs() < average){
            // left <- me
            parent.setSlotKey(parent.getLeft() + 1, this.contents.getDataVal(1), left.blknum);
            this.contents.moveToDest(0, left.contents.getNumRecs(), left.contents);
            if(this.contents.getNumRecs() == 0){
               while(this.contents.getNumRecs() <= average - left.contents.getNumRecs()){
                  // me <- right
                  parent.setSlotKey(parent.getRight(), right.contents.getDataVal(1), this.blknum);
                  right.contents.moveToDest(0, this.contents.getNumRecs(), this.contents);
               }
            }
         }
         while(this.contents.getNumRecs() > average){
            // me -> right
            parent.setSlotKey(parent.getRight(), this.contents.getDataVal(this.contents.getNumRecs() - 1), right.blknum);
            this.contents.moveToDest(this.contents.getNumRecs()-1, 0, right.contents);
         }
         while(this.contents.getNumRecs() < average){
            // me <- right
            parent.setSlotKey(parent.getRight(), right.contents.getDataVal(1), this.blknum);
            right.contents.moveToDest(0, this.contents.getNumRecs(), this.contents);
         }
      }
   }
}
