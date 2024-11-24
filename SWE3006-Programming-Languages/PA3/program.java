import java.io.IOException;
import org.antlr.v4.runtime.*;

import java.util.ArrayList;

class ExprTree {
    ExprNode current;
    ArrayList<ExprTree> children;

    ExprTree() {
        current = new ExprNode();
        children = new ArrayList<>();
    }
}

public class program {

    public static void main(String[] args) throws IOException {
                
        // Get Lexer
        ExprLexer lexer = new ExprLexer(CharStreams.fromStream(System.in));
        
        // Get a list of matched tokens
        CommonTokenStream tokens = new CommonTokenStream(lexer);
        // Pass tokens to parser
        ExprParser parser = new ExprParser(tokens);
        
        // Make AST from prog and print the tree
        ExprParser.ProgContext ctx = parser.prog();
        ExprTree AST = (ExprTree)new BuildAstVisitor().visitProg(ctx);
        AST.children.forEach(node -> new AstCall().Call(node, 0));
        
        // Evaluate AST result
        Evaluate Evaluator = new Evaluate();
        AST.children.forEach(node -> System.out.println(Evaluator.evaluate(node)));
    }
}