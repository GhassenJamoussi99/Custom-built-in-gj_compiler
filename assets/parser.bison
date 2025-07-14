%code requires {
    class Decl;
    class Stmt;
    class Type;
}

/* C PREAMBLE CODE */
%{
#include <stdio.h>
#include <iostream>
#include <map>
#include <string>
#include <sstream>

#include "expr.h"
#include "decl.h"
#include "stmt.h"
#include "symbol.h"
#include "type.h"
#include "param_list.h"
#include "semantic_routines.h"

#include "intel_codegen.h"
#include "typecheck.h"
#include "log.h"
#include "dot_log.h"
#include "dot_gen.h"

extern int yylex();
extern char *yytext;

std::map<std::string, struct expr *> symbolTable; // Use std::string for symbol table keys
std::stringstream dataSection; // To collect .data section entries

int yyerror(const char *s) {
    extern char *yytext;
    extern int yylineno;
    printf("Parse error near token '%s' at line %d: %s\n", yytext, yylineno, s);
    return 1;
}

void print_symbol_table() {
    for (const auto &entry : symbolTable) {
        printf("\n Variable %s = %d\n", entry.first.c_str(), expr_evaluate(entry.second));
    }
}

struct expr *parser_result;
%}

/* declarations */
%debug  /* Enable Bison debug mode */

%union {
    struct expr *expr_ptr;
    Decl *decl;
    Stmt *stmt;
    Type *type;
    struct param_list *param;
    char* expr_id;
    struct expr *string_literal;
}

%token <expr_id> TOKEN_ID
%token <string_literal> TOKEN_STRING_LITERAL
%token <expr_ptr> TOKEN_INT TOKEN_PLUS TOKEN_MINUS TOKEN_MUL TOKEN_DIV TOKEN_SEMI TOKEN_LPAREN TOKEN_RPAREN TOKEN_ASSIGN TOKEN_ERROR
%token TOKEN_IF TOKEN_WHILE TOKEN_PRINT TOKEN_RETURN TOKEN_LBRACE TOKEN_RBRACE TOKEN_COMMA 
%token TOKEN_VOID TOKEN_INT_TYPE TOKEN_BOOLEAN_TYPE TOKEN_STRING_TYPE TOKEN_FOR TOKEN_FUNCTION TOKEN_DPOINTS TOKEN_INCREMENT TOKEN_DECREMENT
%token TOKEN_EQ TOKEN_NEQ TOKEN_LT TOKEN_GT TOKEN_LEQ TOKEN_GEQ TOKEN_TRUE TOKEN_FALSE

%type <decl> program decl_list decl
%type <type> type
%type <param> param_list param_decl
%type <stmt> stmt_list stmt normal_stmt stmt_block
%type <expr_ptr> assignment for_assignment expr term factor call_args call cond

%nonassoc "then"
%nonassoc TOKEN_ELSE

%%
/* grammar rules */
program : decl_list                                                 {
                                                                      $1->resolve();
                                                                      $1->typecheck();

                                                                      //Before folding
                                                                      DOT_LOGCFG.initiate();
                                                                      print_decl_list_dot($1);
                                                                      DOT_LOGCFG.finish();

                                                                      //Fold - Optimize                                                    
                                                                      constant_fold_decls($1);

                                                                      //After folding

                                                                      //Setup new DOT configs for the optimized ast
                                                                      DOT_LOGCFG.OPTIMIZE_FLAG = true;
                                                                      DOT_LOGCFG.updateFilePath();
                                                                      DOT_LOGCFG.clearFile();

                                                                      DOT_LOGCFG.initiate();                                                                   
                                                                      print_decl_list_dot($1);
                                                                      DOT_LOGCFG.finish();

                                                                      //Generate assembly code
                                                                      decl_codegen($1);
                                                                      decl_finish_codegen();
                                                                    }    
        ;

decl_list  
    : decl decl_list                                                { $$ = $1; $1->next = $2; }
    |                                                               { $$ = nullptr; }
    ;

decl
    : TOKEN_ID TOKEN_DPOINTS type TOKEN_SEMI { $$ = new Decl(std::string($1), $3, nullptr, nullptr, nullptr); }
    | TOKEN_ID TOKEN_DPOINTS type TOKEN_ASSIGN expr TOKEN_SEMI { $$ = new Decl(std::string($1), $3, $5, nullptr, nullptr); }
    | TOKEN_ID TOKEN_DPOINTS TOKEN_FUNCTION type TOKEN_LPAREN param_list TOKEN_RPAREN TOKEN_ASSIGN stmt_block { 
                    $$ = new Decl(std::string($1),
                      type_create(TYPE_FUNCTION, $4, $6),
                      nullptr,
                      $9,
                      nullptr);}
    ;
        
type
    : TOKEN_VOID                                                    { $$ = type_create(TYPE_VOID, nullptr, nullptr); }
    | TOKEN_INT_TYPE                                                { $$ = type_create(TYPE_INTEGER, nullptr, nullptr); }
    | TOKEN_BOOLEAN_TYPE                                            { $$ = type_create(TYPE_BOOLEAN, nullptr, nullptr); }
    | TOKEN_STRING_TYPE                                             { $$ = type_create(TYPE_STRING, nullptr, nullptr); }
    ;

param_list
    : /* empty */                                                   { $$ = nullptr; }
    | param_decl                                                    { $$ = $1; }
    | param_list TOKEN_COMMA param_decl                             { $$ = param_list_append($1, $3); }
    ;

param_decl
    : TOKEN_ID TOKEN_DPOINTS type                                   { $$ = param_list_create(std::string($1), $3, nullptr); }
    ;

stmt 
    : TOKEN_IF TOKEN_LPAREN expr TOKEN_RPAREN normal_stmt %prec "then"           { $$ = Stmt::create_if_else($3, $5, nullptr);   LOG(DEBUG) << "stmt_create_if_else:: IF_STMT";}
    | TOKEN_IF TOKEN_LPAREN expr TOKEN_RPAREN normal_stmt TOKEN_ELSE normal_stmt { $$ = Stmt::create_if_else($3, $5, $7);        LOG(DEBUG) << "stmt_create_if_else::IF_ELSE_STMT";}
    | normal_stmt
    ;

normal_stmt
    : TOKEN_WHILE TOKEN_LPAREN expr TOKEN_RPAREN stmt                                           { $$ = new Stmt(STMT_WHILE, nullptr, nullptr, $3, nullptr, $5, nullptr, nullptr); }
    | TOKEN_FOR TOKEN_LPAREN for_assignment TOKEN_SEMI expr TOKEN_SEMI assignment TOKEN_RPAREN stmt { $$ = new Stmt(STMT_FOR, nullptr, $3, $5, $7, $9, nullptr, nullptr); }
    | TOKEN_PRINT call_args TOKEN_SEMI                                                          { $$ = new Stmt(STMT_PRINT, nullptr, nullptr, $2, nullptr, nullptr, nullptr, nullptr); }
    | TOKEN_RETURN expr TOKEN_SEMI                                                              { $$ = new Stmt(STMT_RETURN, nullptr, nullptr, $2, nullptr, nullptr, nullptr, nullptr); }
    | assignment TOKEN_SEMI                                                                     { $$ = new Stmt(STMT_EXPR, nullptr, nullptr, $1, nullptr, nullptr, nullptr, nullptr); }
    | stmt_block                                                                                { $$ = new Stmt(STMT_BLOCK, nullptr, nullptr, nullptr, nullptr, $1, nullptr, nullptr); }
    ;

stmt_block
    : TOKEN_LBRACE stmt_list TOKEN_RBRACE 
        { $$ = $2; }
    ;

stmt_list
    : /* empty */    
        { $$ = nullptr; }
    | stmt_list stmt 
        { $$ = Stmt::list_append($1, $2); }
    | stmt_list decl 
        { $$ = Stmt::list_append($1, new Stmt(STMT_DECL, $2, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr)); }
    ;

for_assignment : assignment
                { $$ = $1; }
                | /* epsilon */
                    { $$ = NULL; }
                ;

assignment
    : TOKEN_ID TOKEN_ASSIGN expr   { $$ = expr_create(EXPR_ASSIGN, expr_create_name(std::string($1)), $3); }
    | TOKEN_ID TOKEN_INCREMENT     { 
        struct expr *new_expr = expr_create(EXPR_ADD, expr_create_name(std::string($1)), expr_create_integer_literal(1));
        $$ = expr_create(EXPR_ASSIGN, expr_create_name(std::string($1)), new_expr); 
      }
    | TOKEN_ID TOKEN_DECREMENT     { 
        struct expr *new_expr = expr_create(EXPR_SUBTRACT, expr_create_name(std::string($1)), expr_create_integer_literal(1));
        $$ = expr_create(EXPR_ASSIGN, expr_create_name(std::string($1)), new_expr); 
      }
    ;

expr
    : expr TOKEN_PLUS term            { $$ = expr_create(EXPR_ADD, $1, $3);}
    | expr TOKEN_MINUS term           { $$ = expr_create(EXPR_SUBTRACT, $1, $3); }
    | cond                            { $$ = $1; }
    | term                            { $$ = $1; }
    ;

cond
    : expr TOKEN_EQ term { $$ = expr_create(EXPR_EQ, $1, $3); }
    | expr TOKEN_NEQ term { $$ = expr_create(EXPR_NEQ, $1, $3); }
    | expr TOKEN_LT term { $$ = expr_create(EXPR_LT, $1, $3);}
    | expr TOKEN_GT term { $$ = expr_create(EXPR_GT, $1, $3); }
    | expr TOKEN_LEQ term { $$ = expr_create(EXPR_LEQ, $1, $3); }
    | expr TOKEN_GEQ term { $$ = expr_create(EXPR_GEQ, $1, $3); }
    ;

term
    : term TOKEN_MUL factor          { $$ = expr_create(EXPR_MULTIPLY,$1,$3); }
    | term TOKEN_DIV factor          { $$ = expr_create(EXPR_DIVIDE,$1,$3); }
    | factor                         { $$ = $1; }
    | call                           { $$ = $1; }
    ;

call
    : TOKEN_ID TOKEN_LPAREN call_args TOKEN_RPAREN { $$ = expr_create(EXPR_CALL, expr_create_name(std::string($1)), $3); }
    ;

call_args
    : /* empty */                    { $$ = nullptr; }
    | expr                           { $$ = expr_list_create($1); }
    | call_args TOKEN_COMMA expr     { $$ = expr_list_append($1, $3); }
    ;

factor
    : TOKEN_MINUS factor             { $$ = expr_create(EXPR_SUBTRACT, expr_create_integer_literal(0),$2); }
    | TOKEN_LPAREN expr TOKEN_RPAREN { $$ = $2; }
    | TOKEN_TRUE                     { $$ = expr_create_boolean_literal(true);}
    | TOKEN_FALSE                    { $$ = expr_create_boolean_literal(false);}
    | TOKEN_STRING_LITERAL           { $$ = expr_create_string_literal(std::string(yytext)); }
    | TOKEN_INT                      { $$ = expr_create_integer_literal(atoi(yytext)); }
    | TOKEN_ID                       { $$ = expr_create_name(std::string($1)); }
%%

