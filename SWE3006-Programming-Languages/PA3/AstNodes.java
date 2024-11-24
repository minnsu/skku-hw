enum node_type {
    ROOT,
    DECL,
    LETIN,
    CALL,
    INFIX,
    NUM,
    VAR,
    NEG
};

class ExprNode {
    node_type type;

    String str; // string value
    Double value; // evaluable value
    ExprNode() {
        ;
    }
}