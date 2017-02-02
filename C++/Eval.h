//
// Created by noah on 2/2/17.
//

#ifndef C_EVAL_H
#define C_EVAL_H

#include "AST.h"

bool eval(Expr *e) {
    struct V : Expr::Visitor {
        bool r;

        void visit(BoolExpr *e) {
            r = e->val;
        };

        void visit(AndExpr *e) {
            r = eval(e->e1) & eval(e->e2);
        };

        void visit(OrExpr *e) {
            r = eval(e->e1) | eval(e->e2);
        };

        void visit(NotExpr *e) {
            r = !eval(e->e1);
        }
    };
    V visitor;
    e->accept(visitor);
    return visitor.r;
}


#endif //C_EVAL_H
