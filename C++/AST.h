//
// Created by noah on 2/2/17.
//

#ifndef C_AST_H
#define C_AST_H

struct Visitor;
struct BoolType;
struct IntType;
struct BoolExpr;
struct AndExpr;
struct OrExpr;
struct NotExpr;

struct Type {
    virtual ~Type() = default;
    struct Visitor;
    virtual void accept(Visitor &) { }
};

struct BoolType : Type {

};

struct IntType : Type {};



struct Expr {
    virtual ~Expr() = default;
    virtual void accept(Visitor &) = 0;
};

struct Expr::Visitor {
    virtual void visit(BoolExpr *) = 0;
    virtual void visit(AndExpr *) = 0;
    virtual void visit(OrExpr *) = 0;
    virtual void visit(NotExpr *) = 0;
};

struct OrExpr : Expr {
	Expr * e1;
    Expr * e2;
    virtual void accept(Visitor & v) {
        v.visit(this);
    }
    OrExpr(Expr * e1, Expr * e2) : e1(e1), e2(e2) { }
};

struct BoolExpr : Expr {
    BoolExpr val;
    BoolExpr (bool b) : val (b) { }
};

struct Context {
    BoolType boolType;
    IntType intType;
};
#endif //C_AST_H
