enum node_type {
    ROOT, ASSIGN, INFIX, NUM, VAR
};

class ExprNode {
    node_type type;

    String str; // Infix or variable
    Double value; // Num
    ExprNode() {
        ;
    }
}