grammar Expr;

// parser rules
prog : (expr ';' NEWLINE?)*; 

expr : expr ('*'|'/') expr  # infixExpr
     | expr ('+'|'-') expr  # infixExpr 
     | num                  # numberExpr
     | id '=' expr          # assignExpr
     | id                   # idExpr
     | '(' expr ')'         # parensExpr
     ;

id : ID ;

num  : INT
     | REAL
     | '-' num
     ;
     
// lexer rules                    
NEWLINE: [\r\n]+ ;
INT: [0-9]+ ;          // should handle negatives
REAL: [0-9]+'.'[0-9]* ; // should handle signs(+/-)
ID: [a-zA-Z_]+;
WS: [ \t\r\n]+ -> skip ;
