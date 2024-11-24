// Generated from /root/PA3/Expr.g4 by ANTLR 4.13.1
import org.antlr.v4.runtime.tree.ParseTreeListener;

/**
 * This interface defines a complete listener for a parse tree produced by
 * {@link ExprParser}.
 */
public interface ExprListener extends ParseTreeListener {
	/**
	 * Enter a parse tree produced by {@link ExprParser#prog}.
	 * @param ctx the parse tree
	 */
	void enterProg(ExprParser.ProgContext ctx);
	/**
	 * Exit a parse tree produced by {@link ExprParser#prog}.
	 * @param ctx the parse tree
	 */
	void exitProg(ExprParser.ProgContext ctx);
	/**
	 * Enter a parse tree produced by {@link ExprParser#decl}.
	 * @param ctx the parse tree
	 */
	void enterDecl(ExprParser.DeclContext ctx);
	/**
	 * Exit a parse tree produced by {@link ExprParser#decl}.
	 * @param ctx the parse tree
	 */
	void exitDecl(ExprParser.DeclContext ctx);
	/**
	 * Enter a parse tree produced by {@link ExprParser#prior_expr}.
	 * @param ctx the parse tree
	 */
	void enterPrior_expr(ExprParser.Prior_exprContext ctx);
	/**
	 * Exit a parse tree produced by {@link ExprParser#prior_expr}.
	 * @param ctx the parse tree
	 */
	void exitPrior_expr(ExprParser.Prior_exprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code letinExpr}
	 * labeled alternative in {@link ExprParser#expr}.
	 * @param ctx the parse tree
	 */
	void enterLetinExpr(ExprParser.LetinExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code letinExpr}
	 * labeled alternative in {@link ExprParser#expr}.
	 * @param ctx the parse tree
	 */
	void exitLetinExpr(ExprParser.LetinExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code varExpr}
	 * labeled alternative in {@link ExprParser#expr}.
	 * @param ctx the parse tree
	 */
	void enterVarExpr(ExprParser.VarExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code varExpr}
	 * labeled alternative in {@link ExprParser#expr}.
	 * @param ctx the parse tree
	 */
	void exitVarExpr(ExprParser.VarExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code infixExpr}
	 * labeled alternative in {@link ExprParser#expr}.
	 * @param ctx the parse tree
	 */
	void enterInfixExpr(ExprParser.InfixExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code infixExpr}
	 * labeled alternative in {@link ExprParser#expr}.
	 * @param ctx the parse tree
	 */
	void exitInfixExpr(ExprParser.InfixExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code negationExpr}
	 * labeled alternative in {@link ExprParser#expr}.
	 * @param ctx the parse tree
	 */
	void enterNegationExpr(ExprParser.NegationExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code negationExpr}
	 * labeled alternative in {@link ExprParser#expr}.
	 * @param ctx the parse tree
	 */
	void exitNegationExpr(ExprParser.NegationExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code numberExpr}
	 * labeled alternative in {@link ExprParser#expr}.
	 * @param ctx the parse tree
	 */
	void enterNumberExpr(ExprParser.NumberExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code numberExpr}
	 * labeled alternative in {@link ExprParser#expr}.
	 * @param ctx the parse tree
	 */
	void exitNumberExpr(ExprParser.NumberExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code callExpr}
	 * labeled alternative in {@link ExprParser#expr}.
	 * @param ctx the parse tree
	 */
	void enterCallExpr(ExprParser.CallExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code callExpr}
	 * labeled alternative in {@link ExprParser#expr}.
	 * @param ctx the parse tree
	 */
	void exitCallExpr(ExprParser.CallExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code parenExpr}
	 * labeled alternative in {@link ExprParser#expr}.
	 * @param ctx the parse tree
	 */
	void enterParenExpr(ExprParser.ParenExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code parenExpr}
	 * labeled alternative in {@link ExprParser#expr}.
	 * @param ctx the parse tree
	 */
	void exitParenExpr(ExprParser.ParenExprContext ctx);
	/**
	 * Enter a parse tree produced by {@link ExprParser#var}.
	 * @param ctx the parse tree
	 */
	void enterVar(ExprParser.VarContext ctx);
	/**
	 * Exit a parse tree produced by {@link ExprParser#var}.
	 * @param ctx the parse tree
	 */
	void exitVar(ExprParser.VarContext ctx);
	/**
	 * Enter a parse tree produced by {@link ExprParser#number}.
	 * @param ctx the parse tree
	 */
	void enterNumber(ExprParser.NumberContext ctx);
	/**
	 * Exit a parse tree produced by {@link ExprParser#number}.
	 * @param ctx the parse tree
	 */
	void exitNumber(ExprParser.NumberContext ctx);
}