public class AstCall {
    AstCall() {
        ;
    }

    public void Call(ExprTree node, int depth) {
        for(int i = 0; i < depth; i++)
            System.out.printf("\t");
        
        switch(node.current.type) {
        case DECL:
        case LETIN:
        case CALL:
        case INFIX:
        case NEG:
        case VAR:
            System.out.println(node.current.str);
            break;
        case NUM:
            System.out.println(node.current.value);
            break;
        default:
            break;
        }

        node.children.forEach(child_node -> new AstCall().Call(child_node, depth + 1));
    }
}