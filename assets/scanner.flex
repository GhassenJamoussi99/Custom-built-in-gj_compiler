/* C PREAMBLE CODE */
%{
#include "token.h"
#include "expr.h"
#include <cstring>
%}

/* declarations */
DIGIT   [0-9]
LETTER  [a-zA-Z]
STRING  \"([^\\"]*|\\(.|\n))*\" 

/* grammar rules */
%%

[ \t\n\r]+                    { /* Ignore whitespace */ }
"//".*                        { /* Ignore comments */ }
"if"                          { return TOKEN_IF; }
"else"                        { return TOKEN_ELSE; }
"while"                       { return TOKEN_WHILE; }
"for"                         { return TOKEN_FOR; }
"print"                       { return TOKEN_PRINT; }
"return"                      { return TOKEN_RETURN; }
"void"                        { return TOKEN_VOID; }
"integer"                     { return TOKEN_INT_TYPE; }
"boolean"                     { return TOKEN_BOOLEAN_TYPE; }
"true"                        { return TOKEN_TRUE; }
"false"                       { return TOKEN_FALSE; }
"string"                      { return TOKEN_STRING_TYPE; }
"function"                    { return TOKEN_FUNCTION; }
{STRING}                      { yylval.string_literal = expr_create_string_literal(strdup(yytext)); return TOKEN_STRING_LITERAL; }
{LETTER}({LETTER}|{DIGIT})*   { yylval.expr_id = strdup(yytext); return TOKEN_ID; }
{DIGIT}+                      { yylval.expr_ptr = expr_create_integer_literal(atoi(yytext)); return TOKEN_INT; }
"+"                           { return TOKEN_PLUS; }
"++"                          { return TOKEN_INCREMENT; }
"-"                           { return TOKEN_MINUS; }
"--"                          { return TOKEN_DECREMENT; }
"*"                           { return TOKEN_MUL; }
"/"                           { return TOKEN_DIV; }
";"                           { return TOKEN_SEMI; }
"("                           { return TOKEN_LPAREN; }
")"                           { return TOKEN_RPAREN; }
"="                           { return TOKEN_ASSIGN; }
"{"                           { return TOKEN_LBRACE; }
"}"                           { return TOKEN_RBRACE; }
","                           { return TOKEN_COMMA; }
":"                           { return TOKEN_DPOINTS; }
"=="                          { return TOKEN_EQ; }
"!="                          { return TOKEN_NEQ; }
"<"                           { return TOKEN_LT; }
">"                           { return TOKEN_GT; }
"<="                          { return TOKEN_LEQ; }
">="                          { return TOKEN_GEQ; }
.                             { return TOKEN_ERROR; }

%%

/* C postamble code */
/*
  yywrap():
    Returns 1 to indicate that there are no more files to be read, 
    which effectively tells the scanner to terminate.
    Returns 0 if there are more files to process, 
    causing the scanner to continue reading the next input file.
 */
int yywrap() { return 1; }
