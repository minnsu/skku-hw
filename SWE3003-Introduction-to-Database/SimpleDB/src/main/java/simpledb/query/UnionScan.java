package simpledb.query;

public class UnionScan implements Scan {
   private Scan s1, s2;
   private boolean s1_valid;

   public UnionScan(Scan s1, Scan s2) {
      this.s1 = s1;
      this.s2 = s2;
      beforeFirst();
   }

   public void beforeFirst() {
      s1.beforeFirst();
      s2.beforeFirst();
   }

   public boolean next() {
      if(s1.next()){
         s1_valid = true;
         return true;
      } else
         s1_valid = false;
      
      if(s2.next())
         return true;
      
      return false;
   }

   public int getInt(String fldname) {
      if (s1_valid && s1.hasField(fldname))
         return s1.getInt(fldname);
      else
         return s2.getInt(fldname);
   }

   public String getString(String fldname) {
      if (s1_valid && s1.hasField(fldname))
         return s1.getString(fldname);
      else
         return s2.getString(fldname);
   }

   public Constant getVal(String fldname) {
      if (s1_valid && s1.hasField(fldname))
         return s1.getVal(fldname);
      else
         return s2.getVal(fldname);
   }

   public boolean hasField(String fldname) {
      return s1.hasField(fldname) && s2.hasField(fldname);
   }

   public void close() {
      s1.close();
      s2.close();
   }
}
