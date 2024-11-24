package simpledb.query;

public class RenameScan implements Scan {
    private Scan s;
    private String fldname_from = null;
    private String fldname_to = null;

    public RenameScan(Scan s, String fldname_from, String fldname_to) {
        this.s = s;
        this.fldname_from = fldname_from;
        this.fldname_to = fldname_to;
    }

    public void beforeFirst() {
        s.beforeFirst();
    }

    public boolean next() {
        if (s.next())
           return true;
        else {
           return false;
        }
    }

    public int getInt(String fldname) {
        if(fldname.equals(fldname_to))
            fldname = fldname_from;
        if (s.hasField(fldname))
            return s.getInt(fldname);
        else
            throw new RuntimeException("field " + fldname + " not found.");
        }
        
    public String getString(String fldname) {
        if(fldname.equals(fldname_to))
            fldname = fldname_from;
        if (s.hasField(fldname))
            return s.getString(fldname);
        else
            throw new RuntimeException("field " + fldname + " not found.");
        }
        
    public Constant getVal(String fldname) {
        if(fldname.equals(fldname_to))
            fldname = fldname_from;
        if (s.hasField(fldname))
            return s.getVal(fldname);
        else
            throw new RuntimeException("field " + fldname + " not found.");
    }

    public boolean hasField(String fldname) {
        return fldname_to.equals(fldname);
    }

    public void close() {
        s.close();
    }
}
