public class BuildAstVisitor extends ExprBaseVisitor<ExprTree>{

    @Override
    public ExprTree visitProg(ExprParser.ProgContext ctx) {
        
        ExprTree prog = new ExprTree();
        prog.current.type = node_type.ROOT;
        for(int i = 0; i < ctx.expr().size(); i++)
            prog.children.add(visit(ctx.expr(i)));
        
        return prog;
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

    Integer sign = 1;
    @Override
    public ExprTree visitNum(ExprParser.NumContext ctx) {
        ExprTree node = new ExprTree();
        node.current.type = node_type.NUM;

        Double result = 0.0;
        if(ctx.num() != null) { // negative num
            sign = -1;
            return visit(ctx.num());
        }
        else if(ctx.INT() != null)
            result = sign * Double.parseDouble(ctx.INT().getText());
        else
            result = sign * Double.parseDouble(ctx.REAL().getText());
        
        node.current.value = result;
        sign = 1;
        return node;
    }

    @Override
    public ExprTree visitNumberExpr(ExprParser.NumberExprContext ctx) {
        return visit(ctx.num());
    }


    @Override
    public ExprTree visitId(ExprParser.IdContext ctx) {
        ExprTree node = new ExprTree();
        node.current.type = node_type.VAR;
        node.current.str = ctx.ID().getText();
        
        return node;
    }
    @Override
    public ExprTree visitIdExpr(ExprParser.IdExprContext ctx) {
        return visit(ctx.id());
    }

    @Override
    public ExprTree visitParensExpr(ExprParser.ParensExprContext ctx) {
        return visit(ctx.expr());
    }

    @Override
    public ExprTree visitAssignExpr(ExprParser.AssignExprContext ctx) {
        ExprTree node = new ExprTree();
        node.current.type = node_type.ASSIGN;
        node.current.str = "ASSIGN";

        node.children.add(visit(ctx.id()));
        node.children.add(visit(ctx.expr()));

        return node;
    }
}