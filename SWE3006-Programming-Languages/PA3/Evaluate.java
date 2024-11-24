import java.util.ArrayList;
import java.util.HashMap;

public class Evaluate {
    HashMap<String, Double> variables;
    
    class Closure {
        public ArrayList<String> param_list;
        public ExprTree body;
    };

    HashMap<String, Closure> functions;
    Evaluate() {
        variables = new HashMap<>();
        functions = new HashMap<>();
        ;
    }

    Double evaluate(ExprTree node) {
        Double result = 0.0;
        Double left = 0.0;
        Double right = 0.0;
        Closure closure = new Closure();
        
        int n_params = 0;
        String fname = "";
        switch(node.current.type) {
        case DECL:
            fname = node.children.get(0).current.str;

            n_params = node.children.size() - 2;
            ArrayList<String> params = new ArrayList<>();
            for(int i = 0; i < n_params; i++) {
                params.add(node.children.get(1+i).current.str);
            }
            ExprTree body = node.children.get(node.children.size()-1);
            
            closure.param_list = params;
            closure.body = body;
            
            functions.put(fname, closure);
            break;
        
        case LETIN:
            String id = node.children.get(0).current.str;
            Double value = evaluate(node.children.get(1));
            
            Double shadowing = null;
            if(variables.containsKey(id))
                shadowing = variables.get(id);

            variables.put(id, value);
            result = evaluate(node.children.get(2));

            if(shadowing != null)
                variables.put(id, shadowing);
            break;
        
        case CALL:
            HashMap<String, Double> env_backup = new HashMap<>(variables);
        
            fname = node.children.get(0).current.str;
            closure = functions.get(fname);

            if(node.children.size() > 1) { // have parameters
                ArrayList<Double> evaluated = new ArrayList<>();
                for(int i = 1; i < node.children.size(); i++)
                    evaluated.add(evaluate(node.children.get(i)));

                variables = new HashMap<>();
                for(int i = 0; i < closure.param_list.size(); i++) {
                    String param_name = closure.param_list.get(i);
                    variables.put(param_name, evaluated.get(i));
                }
            }
            result = evaluate(closure.body);
            
            variables = env_backup;
            break;
        
        case NEG:
            result = -1 * evaluate(node.children.get(0));
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
            break;
        default:
            break;
        }
        return result;
    }
}