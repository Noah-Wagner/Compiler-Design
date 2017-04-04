//
// Created by Noah Wagner on 4/3/17.
//

#ifndef C_STATEMENT_H
#define C_STATEMENT_H

#include "Expr.h"

struct Statement {


};

struct ExprStmt : Statement {

    Expr * expr;

    ExprStmt(Expr * e) : expr(e) {};

};

#endif //C_STATEMENT_H
