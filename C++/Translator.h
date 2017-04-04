//
// Created by Noah Wagner on 4/3/17.
//

#ifndef C_TRANSLATOR_H
#define C_TRANSLATOR_H

#include "Expr.h"
#include "Token.h"
#include "Statement.h"


struct Translator {

    ExprStmt * GetExprStmt(Expr * e1) {
        return new ExprStmt(e1);
    }

    Expr * GetAddExpr(Expr * e1, Expr * e2) {
        return new AddExpr(e1, e2);
    }

    Expr * GetSubExpr(Expr * e1, Expr * e2) {
        return new SubExpr(e1, e2);
    }

    Expr * GetMulExpr(Expr * e1, Expr * e2) {
        return new MultiExpr(e1, e2);
    }

    Expr * GetDivExpr(Expr * e1, Expr * e2) {
        return new DivExpr(e1, e2);
    }

    Expr * GetModExpr(Expr * e1, Expr * e2) {
        return new ModExpr(e1, e2);
    }

    Expr * GetNegExpr(Expr * e1) {
        return new NegExpr(e1);
    }

    Expr * GetIntExpr(Token * token) {
        return new IntExpr(std::stoi(token->attribute));
    }

    Expr * GetBoolExpr(Token * token) {
        return new BoolExpr(token->attribute == "1");
    }

};

#endif //C_TRANSLATOR_H
