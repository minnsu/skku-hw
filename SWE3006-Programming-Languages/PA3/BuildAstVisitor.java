import java.util.ArrayList;
import java.util.HashMap;
import java.util.regex.Pattern;

public class BuildAstVisitor extends ExprBaseVisitor<ExprTree>{
    private ArrayList<String> variables;
    private ArrayList<String> functions;
    private HashMap<String, Integer> arguments_count;
    private ArrayList<String> semanticErrors;

    private Boolean semanticEnable = true;

    enum _id {
        function, parameter, variable
    };
    private void test_regex(String target, _id id) {
        String regex = "";
        switch (id) {
            case function:
                regex = "[a-zA-Z0-9]+";
                break;
            case parameter:
                regex = "[a-zA-Z_]+";
                break;
            case variable:
                regex = "[a-zA-Z_-]+";
                break;
        }
        if( ! Pattern.matches(regex, target) ) {
            // System.out.println("DEBUG => " + id.toString() + " identifier " + target + " does not match to regex " + regex);
        }
    }

    @Override
    public ExprTree visitProg(ExprParser.ProgContext ctx) {
        variables = new ArrayList<>();
        functions = new ArrayList<>();
        arguments_count = new HashMap<>();
        semanticErrors = new ArrayList<>();
        
        ExprTree prog = new ExprTree();
        prog.current.type = node_type.ROOT;
        
        for(int i = 0; i < ctx.decl().size(); i++)
            prog.children.add(visit(ctx.decl(i)));
        prog.children.add(visit(ctx.expr()));

        if(!semanticErrors.isEmpty()) {
            for(int i = 0; i < semanticErrors.size(); i++)
                System.out.println(semanticErrors.get(i));
            
            System.exit(0);
        }
        return prog;
    }

    @Override
    public ExprTree visitDecl(ExprParser.DeclContext ctx) {
        ExprTree node = new ExprTree();
        node.current.type = node_type.DECL;
        node.current.str = "DECL";

        // Add to <functions> and <function, argc>
        functions.add(ctx.var(0).getText());
        arguments_count.put(ctx.var(0).getText(), ctx.var().size()-1);

        // When visit function name and parameter var, disable semantic error.
        semanticEnable = false;
        
        test_regex(ctx.var(0).getText(), _id.function);
        node.children.add(visit(ctx.var(0)));
        
        for(int i = 1; i < ctx.var().size(); i++) {
            test_regex(ctx.var(i).getText(), _id.parameter);
            node.children.add(visit(ctx.var(i)));
            
            // Temporally add paramter to declared variable list
            variables.add(ctx.var(i).getText());
        }

        // When visit function body, enable semantic error
        semanticEnable = true;
        node.children.add(visit(ctx.expr()));
        
        // Remove parameters from declared variables list after visit body.
        for(int i = 1; i < ctx.var().size(); i++)
            variables.remove(variables.size()-1);
        return node;
    }

    @Override
    public ExprTree visitVar(ExprParser.VarContext ctx) {
        ExprTree node = new ExprTree();

        try {
            Double tmp = Double.parseDouble(ctx.ID().getText());
            if(semanticEnable) {
                node.current.type = node_type.NUM;
                node.current.value = tmp;
                return node;
            }
        } catch (NumberFormatException e) {
        }

        node.current.type = node_type.VAR;
        node.current.str = ctx.ID().getText();
                
        if(semanticEnable && !variables.contains(node.current.str))
            semanticErrors.add(String.format("Error: Free identifier %s detected.", node.current.str));
        return node;
    }

    @Override
    public ExprTree visitLetinExpr(ExprParser.LetinExprContext ctx) {
        ExprTree node = new ExprTree();
        node.current.type = node_type.LETIN;
        node.current.str = "LETIN";

        // When visit var in LetIn, disable semantic error.
        semanticEnable = false;
        test_regex(ctx.var().getText(), _id.variable);
        node.children.add(visit(ctx.var()));
        
        // When visit first expr in LetIn, enable semantic error.
        semanticEnable = true;
        node.children.add(visit(ctx.expr()));
        // LetIn declared variable must be added after first expr evalution.
        variables.add(ctx.var().getText());

        node.children.add(visit(ctx.prior_expr()));

        // Remove current variable after evalution of last expr
        variables.remove(variables.size() - 1);
        return node;
    }

    @Override
    public ExprTree visitCallExpr(ExprParser.CallExprContext ctx) {
        ExprTree node = new ExprTree();
        node.current.type = node_type.CALL;
        node.current.str = "CALL";
        String fname = ctx.var().getText();

        // When visit function name, disable semantic error.
        semanticEnable = false;
        test_regex(fname, _id.function);
        node.children.add(visit(ctx.var()));
        
        // When visit evaluation arguments, enable semantic error.
        semanticEnable = true;
        for(int i = 0; i < ctx.expr().size(); i++)
            node.children.add(visit(ctx.expr(i)));
        
        // Semantic error processing.
        if(!functions.contains(fname)) { // Undefined function call
            semanticErrors.add(String.format("Error: Undefined function %s detected.", fname));
        } else { // # of arguments mismatch
            int required = arguments_count.get(fname);
            int actual = ctx.expr().size();
            if(required != actual) {
                semanticErrors.add(String.format("Error: The number of arguments of %s mismatched, Required: %d, Actual: %d",
                    fname, required, actual));
            }
        }
        return node;
    }

    @Override
    public ExprTree visitInfixExpr(ExprParser.InfixExprContext ctx) {
        ExprTree node = new ExprTree();
        node.current.type = node_type.INFIX;

        String op = ctx.getChild(1).getText();
        switch(op) {
        case "*":
            node.current.str = "MUL";
            break;
        case "/":
            node.current.str = "DIV";
            break;
        case "+":
            node.current.str = "ADD";
            break;
        case "-":
            node.current.str = "SUB";
            break;
        }

        node.children.add(visit(ctx.expr(0)));
        node.children.add(visit(ctx.expr(1)));
        return node;
    }

    @Override
    public ExprTree visitParenExpr(ExprParser.ParenExprContext ctx) {
        return visit(ctx.expr());
    }

    @Override
    public ExprTree visitNumberExpr(ExprParser.NumberExprContext ctx) {
        return visit(ctx.number());
    }

    Integer sign = 1;
    @Override
    public ExprTree visitNumber(ExprParser.NumberContext ctx) {
        ExprTree node = new ExprTree();
        node.current.type = node_type.NUM;

        Double result = 0.0;
        if(ctx.number() != null) {
            sign = -1;
            return visit(ctx.number());
        } else if(ctx.INT() != null)
            result = sign * Double.parseDouble(ctx.INT().getText());
        else
            result = sign * Double.parseDouble(ctx.REAL().getText());
        
        node.current.value = result;
        sign = 1;
        return node;
    }

    @Override
    public ExprTree visitNegationExpr(ExprParser.NegationExprContext ctx) {
        ExprTree node = new ExprTree();
        node.current.type = node_type.NEG;
        node.current.str = "NEGATE";

        node.children.add(visit(ctx.expr()));

        return node;
    }

    @Override
    public ExprTree visitVarExpr(ExprParser.VarExprContext ctx) {
        try {
            Double.parseDouble(ctx.var().getText());
        } catch (NumberFormatException e) {
            test_regex(ctx.var().getText(), _id.variable);
        }
        return visit(ctx.var());
    }

    @Override
    public ExprTree visitPrior_expr(ExprParser.Prior_exprContext ctx) {
        return visit(ctx.expr());
    }
}