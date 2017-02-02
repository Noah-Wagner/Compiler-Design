//
// Created by noah on 2/2/17.
//

#ifndef C_AST_H
#define C_AST_H

struct BoolExpr;
struct AndExpr;
struct OrExpr;
struct NotExpr;

struct Expr {
    virtual ~Expr() = default;

    struct Visitor;

    virtual void accept(Expr::Visitor &) = 0;
};

struct Expr::Visitor {
    virtual void visit(BoolExpr *) = 0;

    virtual void visit(AndExpr *) = 0;

    virtual void visit(OrExpr *) = 0;

    virtual void visit(NotExpr *) = 0;
};

struct BoolExpr : Expr {
    bool val;

    virtual void accept(Visitor &v) {
        v.visit(this);
    }

    BoolExpr(bool b) : val(b) {}
};

struct NotExpr : Expr {
    Expr *e1;

    virtual void accept(Visitor &v) {
        v.visit(this);
    }

    NotExpr(Expr *e1) : e1(e1) {}
};

struct AndExpr : Expr {
    Expr *e1;
    Expr *e2;

    virtual void accept(Visitor &v) {
        v.visit(this);
    }

    AndExpr(Expr *e1, Expr *e2) : e1(e1), e2(e2) {}
};

struct OrExpr : Expr {
    Expr *e1;
    Expr *e2;

    virtual void accept(Visitor &v) {
        v.visit(this);
    }

    OrExpr(Expr *e1, Expr *e2) : e1(e1), e2(e2) {}
};

#endif //C_AST_H
