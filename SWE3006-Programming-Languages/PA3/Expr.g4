grammar Expr;

// parser rules
prog : decl* expr ';' ; 

decl : 'def' var var* '=' expr 'endef' ;

prior_expr : expr ;
expr : 'let' var '=' expr 'in' prior_expr    # letinExpr
     | var '(' (expr (',' expr)*)? ')'       # callExpr
     | expr ('*'|'/') expr                   # infixExpr
     | expr ('+'|'-') expr                   # infixExpr
     | '(' expr ')'                          # parenExpr
     | number                                # numberExpr
     | '~' '(' expr ')'                      # negationExpr
     | var                                   # varExpr
     ;

var : ID ;

number : INT
     | REAL
     | '-' number
     ;

// lexer rules                    
ID: ([a-zA-Z0-9_-] | '.')+;
// FUNCTION: [a-zA-Z0-9]+ ;
// PARAMETER: [a-zA-Z_]+ ;
// VARIABLE: [a-zA-Z_-]+ ;

INT: [0-9]+ ;          // should handle negatives
REAL: [0-9]+'.'[0-9]* ; // should handle signs(+/-)

NEWLINE: [\r\n]+ ;
WS: [ \t\r\n]+ -> skip ;