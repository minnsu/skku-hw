import java.util.HashMap;

public class Evaluate {
    HashMap<String, Double> variables;
    Evaluate() {
        variables = new HashMap<>();
        ;
    }

    Double evaluate(ExprTree node) {
        Double result = 0.0;
        Double left = 0.0;
        Double right = 0.0;
        switch(node.current.type) {
        case ASSIGN:
            String id = node.children.get(0).current.str;
            Double value = evaluate(node.children.get(1));
            variables.put(id, value);
            break;
        case INFIX:
            left = evaluate(node.children.get(0));
            right = evaluate(node.children.get(1));
            switch(node.current.str) {
            case "MUL":
                result = left * right;
                break;
            case "DIV":
                result = left / right;
                break;
            case "ADD":
                result = left + right;
                break;
            case "SUB":
                result = left - right;
                break;
            }
            break;
        case NUM:
            result = node.current.value;
            break;
        case VAR:
            result = variables.get(node.current.str);
        }
        return result;
    }
}