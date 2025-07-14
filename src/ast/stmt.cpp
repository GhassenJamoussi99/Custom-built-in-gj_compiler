#include <iostream>
#include <cstdlib>

#include "stmt.h"
#include "decl.h"
#include "symbol.h"
#include "log.h"
#include "asm_log.h"
#include "scratch.h"

Stmt::Stmt(stmt_t kind, Decl *decl, expr *init_expr, expr *expr_value, expr *next_expr, Stmt *body, Stmt *else_body, Stmt *next)
	: kind(kind), decl(decl), init_expr(init_expr), expr_value(expr_value), next_expr(next_expr), body(body), else_body(else_body), next(next) {}

Stmt* Stmt::create_if_else(expr *expr_value, Stmt *body, Stmt *else_body) {
	return new Stmt(STMT_IF_ELSE, nullptr, nullptr, expr_value, nullptr, body, else_body, nullptr);
}

Stmt* Stmt::list_append(Stmt *list, Stmt *stmt) {
	if (!list) return stmt;
	Stmt *current = list;
	while (current->next) current = current->next;
	current->next = stmt;
	return list;
}

void Stmt::resolve() {
	LOG(INFO) << "stmt_resolve::";
	switch (kind) {
		case STMT_DECL:
			LOG(INFO) << "stmt_resolve::Resolving declaration statement";
			if (decl) decl->resolve();
			break;
		case STMT_EXPR:
			LOG(INFO) << "stmt_resolve::Resolving expression statement";
			expr_resolve(expr_value);
			break;
		case STMT_IF_ELSE:
			LOG(INFO) << "stmt_resolve::Resolving if-else statement";
			expr_resolve(expr_value);
			if (body) body->resolve();
			if (else_body) else_body->resolve();
			break;
		case STMT_FOR:
			LOG(INFO) << "stmt_resolve::Resolving for loop statement";
			if (init_expr) expr_resolve(init_expr);
			if (expr_value) expr_resolve(expr_value);
			if (next_expr) expr_resolve(next_expr);
			if (body) body->resolve();
			break;
		case STMT_PRINT:
			LOG(INFO) << "stmt_resolve::Resolving print statement";
			expr_resolve(expr_value);
			break;
		case STMT_WHILE:
			LOG(INFO) << "stmt_resolve::Resolving while loop statement";
			expr_resolve(expr_value);
			if (body) body->resolve();
			break;
		case STMT_RETURN:
			LOG(INFO) << "stmt_resolve::Resolving return statement";
			expr_resolve(expr_value);
			break;
		case STMT_BLOCK:
			LOG(INFO) << "stmt_resolve::Resolving block statement";
			if (body) body->resolve();
			break;
		case STMT_FUNCTION:
			LOG(INFO) << "stmt_resolve::Resolving function statement";
			if (body) body->resolve();
			break;
		default:
			LOG(ERROR) << "stmt_resolve::Unknown statement type encountered." << Stmt::to_string(kind);
			exit(EXIT_FAILURE);
			break;
	}
	if (next) next->resolve();
}

std::string Stmt::to_string(stmt_t kind) {
	switch (kind) {
		case STMT_DECL: return "STMT_DECL";
		case STMT_EXPR: return "STMT_EXPR";
		case STMT_IF_ELSE: return "STMT_IF_ELSE";
		case STMT_FOR: return "STMT_FOR";
		case STMT_PRINT: return "STMT_PRINT";
		case STMT_WHILE: return "STMT_WHILE";
		case STMT_FUNCTION: return "STMT_FUNCTION";
		case STMT_RETURN: return "STMT_RETURN";
		case STMT_BLOCK: return "STMT_BLOCK";
		default: return "UNKNOWN_STATEMENT_KIND";
	}
}

void Stmt::typecheck() {
//TODO
}

// TODO: Implement Stmt::typecheck as a member function, moving logic from stmt_typecheck
