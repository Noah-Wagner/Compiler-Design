//
// Created by Noah Wagner on 4/3/17.
//

#ifndef C_PARSER_H
#define C_PARSER_H

#include "Lexer.h"
#include "Expr.h"
#include "Expr.h"
#include "Statement.h"
#include "Translator.h"

struct Parser {

	Translator trans;
	std::vector<Token *> tokens;
	std::vector<Token *>::iterator iter;

	Parser(std::vector<Token *> tokens) : tokens(tokens), iter(tokens.begin()) {};


	static ExprStmt * Parse(std::vector<Token *> tokens) {

		Parser parser(tokens);
		ExprStmt * stmt = parser.GetStatement();

		return stmt;
	}

	static ExprStmt * Parse(std::string str) {
		return Parse(Lexer::Lexe(str));
	}

	Token * Poll() {
		if (iter == tokens.end()) {
			return nullptr;
		} else {
			return *iter++;
		}
	}

	Token * Peek() {
		try {
			if (iter == tokens.end()) {
				return nullptr;
			} else {
				return *iter;
			}
		} catch (...) {
			return nullptr;
		}
	}

	TOKEN_KIND PeekType() {
		if (Token * token = Peek()) {
			return token->kind;
		}
		return EOFTok;
	}

	// A totally original method

	// Removes and returns the HEAD token if it is equal to the type
	// Otherwise returns null
	Token * Match(TOKEN_KIND type) {
		if (PeekType() == type) {
			return Poll();
		} else {
			return nullptr;
		}
	}

	ExprStmt * GetStatement();
	ExprStmt * GetExprStmt();
	Expr * GetExpression();
	Expr * GetAddExpr();
	Expr * GetMultiExpr();
	Expr * GetUnaryExpr();
	Expr * GetPrimaryExpr();


	Expr * GetOrderExpr();

	Expr * GetEqExpr();

	Expr * GetAndExpr();

	Expr * GetOrExpr();

	Expr * GetBitAndExpr();

	Expr * GetBitOrExpr();

	Expr * GetBitXorExpr();
};

ExprStmt * Parser::GetStatement() {
	return GetExprStmt();
}

ExprStmt * Parser::GetExprStmt() {
	Expr * expr = GetExpression();
	return trans.GetExprStmt(expr);
}

Expr * Parser::GetExpression() {
	return GetOrExpr();
}

Expr * Parser::GetOrExpr() {
	Expr * e1 = GetAndExpr();
	while (true) {
		if (Match(AndTok)) {
			Expr * e2 = GetAndExpr();
			e1 = trans.GetOrExpr(e1, e2);
		} else {
			break;
		}
	}
	return e1;
}

Expr * Parser::GetAndExpr() {
	Expr * e1 = GetBitOrExpr();
	while (true) {
		if (Match(AndTok)) {
			Expr * e2 = GetBitOrExpr();
			e1 = trans.GetAndExpr(e1, e2);
		} else {
			break;
		}
	}
	return e1;
}
// OR XOR AND

Expr * Parser::GetBitOrExpr() {
	Expr * e1 = GetBitXorExpr();
	while (true) {
		if (Match(BitOrTok)) {
			Expr * e2 = GetBitXorExpr();
			e1 = trans.GetBitOrExpr(e1, e2);
		} else {
			break;
		}
	}
	return e1;
}

Expr * Parser::GetBitXorExpr() {
	Expr * e1 = GetBitAndExpr();
	while (true) {
		if (Match(BitXorTok)) {
			Expr * e2 = GetBitAndExpr();
			e1 = trans.GetBitXorExpr(e1, e2);
		} else {
			break;
		}
	}
	return e1;
}

Expr * Parser::GetBitAndExpr() {
	Expr * e1 = GetEqExpr();
	while (true) {
		if (Match(BitAndTok)) {
			Expr * e2 = GetEqExpr();
			e1 = trans.GetBitAndExpr(e1, e2);
		} else {
			break;
		}
	}
	return e1;
}

Expr * Parser::GetEqExpr() {
	Expr * e1 = GetOrderExpr();
	while (true) {
		if (Match(EqTok)) {
			Expr * e2 = GetOrderExpr();
			e1 = trans.GetEqExpr(e1, e2);
		} else if (Match(NeqTok)) {
			Expr * e2 = GetOrderExpr();
			e1 = trans.GetNeqExpr(e1, e2);
		} else {
			break;
		}
	}
	return e1;
}

Expr * Parser::GetOrderExpr() {
	Expr * e1 = GetAddExpr();
	while (true) {
		if (Match(LtTok)) {
			Expr * e2 = GetAddExpr();
			e1 = trans.GetLtExpr(e1, e2);
		} else if (Match(LtEqTok)) {
			Expr * e2 = GetAddExpr();
			e1 = trans.GetLtEqExpr(e1, e2);
		} else if (Match(GtTok)) {
			Expr * e2 = GetAddExpr();
			e1 = trans.GetGtExpr(e1, e2);
		} else if (Match(GtEqTok)) {
			Expr * e2 = GetAddExpr();
			e1 = trans.GetGtEqExpr(e1, e2);
		} else {
			break;
		}
	}
	return e1;
}

Expr * Parser::GetAddExpr() {
	Expr * e1 = GetMultiExpr();
	while (true) {
		if (Match(AddTok)) {
			Expr * e2 = GetMultiExpr();
			e1 = trans.GetAddExpr(e1, e2);
		} else if (Match(SubTok)) {
			Expr * e2 = GetMultiExpr();
			e1 = trans.GetSubExpr(e1, e2);
		} else {
			break;
		}
	}
	return e1;
}

Expr * Parser::GetMultiExpr() {
	Expr * e1 = GetUnaryExpr();
	Expr * e2;
	while (true) {
		if (Match(MulTok)) {
			e2 = GetUnaryExpr();
			e1 = trans.GetMulExpr(e1, e2);
		} else if (Match(DivTok)) {
			e2 = GetUnaryExpr();
			e1 = trans.GetDivExpr(e1, e2);
		} else if (Match(ModTok)) {
			e2 = GetUnaryExpr();
			e1 = trans.GetModExpr(e1, e2);
		} else {
			break;
		}
	}
	return e1;
}

Expr * Parser::GetUnaryExpr() {
	if (Match(SubTok)) {
		Expr * e1 = GetUnaryExpr();
		return trans.GetNegExpr(e1);
	} else if (Match(NotTok)) {
		Expr * e1 = GetUnaryExpr();
		return trans.GetNotExpr(e1);
	}
	return GetPrimaryExpr();
}

Expr * Parser::GetPrimaryExpr() {
	switch (Peek()->kind) {
		case BoolTok:
			return trans.GetBoolExpr(Poll());
		case IntTok:
			return trans.GetIntExpr(Poll());
		case CommTok:
			return nullptr;
		default:
			throw std::runtime_error("OH NO");
	}
	// TODO: Error case
}

#endif //C_PARSER_H
