//
// Created by Noah Wagner on 2/2/17.
//

#ifndef C_TYPE_H
#define C_TYPE_H

#include "AST.h"

TYPE Type(Expr *e) {
    struct V : Expr::Visitor {
        TYPE r;
        void visit(BoolExpr *e) {
            r = TYPE::BoolType;
        }
        void visit(AndExpr *e) {
            r = TYPE::BoolType;
        }
        void visit(NotExpr *e) {
            r = TYPE::BoolType;
        }
        void visit(OrExpr *e) {
            r = TYPE::BoolType;
        }
        void visit(XorExpr *e) {
            r = TYPE::BoolType;
        }
        void visit(AddExpr *e) {
            r = TYPE::IntType;
        }
        void visit(IntExpr *e) {
            r = TYPE::IntType;
        }
        void visit(SubExpr *e) {
            r = TYPE::IntType;
        }
        void visit(MultiExpr *e) {
            r = TYPE::IntType;
        }
        void visit(DivExpr *e) {
            r = TYPE::IntType;
        }
        void visit(ModExpr *e) {
            r = TYPE::IntType;
        }
        void visit(EqExpr *e) {
            r = TYPE::BoolType;
        }
        void visit(NeqExpr *e) {
            r = TYPE::BoolType;
        }
        void visit(NegExpr *e) {
            r = TYPE::IntType;
        }
        void visit(GeqExpr *e) {
            r = TYPE::BoolType;
        }
        void visit(GeExpr *e) {
            r = TYPE::BoolType;
        }
        void visit(LeExpr *e) {
            r = TYPE::BoolType;
        }
        void visit(LeqExpr *e) {
            r = TYPE::BoolType;
        }
        void visit(CondExpr *e) {
            r = Type(e->e2);
        }
        void visit(AndThenExpr *e) {
            r = TYPE::BoolType;
        }
        void visit(OrElseExpr *e) {
            r = TYPE::BoolType;
        }

    };
    V visitor;
    e->accept(visitor);
    return visitor.r;
}


#endif //C_TYPE_H
