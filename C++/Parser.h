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

    Token * Poll() {
        if (iter == tokens.end()) {
            return nullptr;
        } else {
            return *iter++;
        }
    }

    Token * Peek() {
        if (iter == tokens.end()) {
            return nullptr;
        } else {
            return *iter;
        }
    }

    TOKEN_KIND PeekType() {
        if (Token * token = Peek()) {
            return token->kind;
        }
        return EOFTok;
    }

    // A totally original method
    Token * Match(TOKEN_KIND type) {
        if (PeekType() == type) {
            return Poll();
        } else {
            return nullptr;
        }
    }

    Expr * GetPrimaryExpr() {
        switch (Peek()->kind) {
            case BoolTok:
                return trans.GetBoolExpr(Poll());
            case IntTok:
                return trans.GetIntExpr(Poll());
        }
        // TODO: Error case
    }

    Expr * GetUnaryExpr() {
        if (Match(SubTok)) {
            Expr * e1 = GetUnaryExpr();
            return trans.GetNegExpr(e1);
        }
        return GetPrimaryExpr();
    }

    Expr * GetMultiExpr() {
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

    Expr * GetAddExpr() {
        Expr * e1 = GetMultiExpr();
        Expr * e2;
        while (true) {
            if (Match(AddTok)) {
                e2 = GetMultiExpr();
                e1 = trans.GetAddExpr(e1, e2);
            } else if (Match(SubTok)) {
                e2 = GetMultiExpr();
                e1 = trans.GetSubExpr(e1, e2);
            } else {
                break;
            }
        }
        return e1;
    }

    Expr * GetExpression() {
        return GetAddExpr();
    }

    ExprStmt * GetExprStmt() {
        Expr * expr = GetExpression();
        return trans.GetExprStmt(expr);
    }

    ExprStmt * GetStatement() {
        return GetExprStmt();
    }

};

#endif //C_PARSER_H
