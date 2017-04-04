//
// Created by Noah Wagner on 4/3/17.
//

#ifndef C_STATEMENT_H
#define C_STATEMENT_H

#include "Expression.h"

struct Statement {


};

struct Expr_Stmt : Statement {

    Expression * expr;

    Expr_Stmt(Expression * e) : expr(e) {};

};

#endif //C_STATEMENT_H
