//
// Created by noah on 2/2/17.
//

#ifndef C_AST_H
#define C_AST_H

struct BoolType;
struct IntType;

struct BoolExpr;
struct AndExpr;
struct OrExpr;
struct NotExpr;
struct XorExpr;


struct IntExpr;
struct AddExpr;
struct SubExpr;
struct MultiExpr;
struct DivExpr;
struct ModExpr;
struct NegExpr;

struct EqExpr;
struct NeqExpr;
struct LeExpr;
struct GeExpr;
struct LeqExpr;
struct GeqExpr;

struct CondExpr;
struct AndThenExpr;
struct OrElseExpr;

enum class TYPE {
    IntType,
    BoolType,
};

struct Type {
    virtual ~Type() = default;
};

struct BoolType : Type {
};
struct IntType : Type {
};

struct Expr {
    virtual ~Expr() = default;

    struct Visitor;

    virtual void accept(Expr::Visitor &) = 0;
};


struct Expr::Visitor {
    virtual void visit(BoolExpr *) = 0;

    virtual void visit(AndExpr *) = 0;

    virtual void visit(OrExpr *) = 0;

    virtual void visit(XorExpr *) = 0;

    virtual void visit(NotExpr *) = 0;

    virtual void visit(IntExpr *) = 0;

    virtual void visit(AddExpr *) = 0;

    virtual void visit(SubExpr *) = 0;

    virtual void visit(MultiExpr *) = 0;

    virtual void visit(DivExpr *) = 0;

    virtual void visit(ModExpr *) = 0;

    virtual void visit(NegExpr *) = 0;

    virtual void visit(EqExpr *) = 0;

    virtual void visit(NeqExpr *) = 0;

    virtual void visit(GeExpr *) = 0;

    virtual void visit(GeqExpr *) = 0;

    virtual void visit(LeExpr *) = 0;

    virtual void visit(LeqExpr *) = 0;

    virtual void visit(CondExpr *) = 0;

    virtual void visit(AndThenExpr *) = 0;

    virtual void visit(OrElseExpr *) = 0;

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

struct XorExpr : Expr {
    Expr *e1;
    Expr *e2;

    virtual void accept(Visitor &v) {
        v.visit(this);
    }

    XorExpr(Expr *e1, Expr *e2) : e1(e1), e2(e2) {}
};

struct IntExpr : Expr {
    int val;

    virtual void accept(Visitor &v) {
        v.visit(this);
    }

    IntExpr(int i) : val(i) {}
};

struct AddExpr : Expr {
    Expr *e1;
    Expr *e2;

    virtual void accept(Visitor &v) {
        v.visit(this);
    }

    AddExpr(Expr *e1, Expr *e2) : e1(e1), e2(e2) {}
};

struct SubExpr : Expr {
    Expr *e1;
    Expr *e2;

    virtual void accept(Visitor &v) {
        v.visit(this);
    }

    SubExpr(Expr *e1, Expr *e2) : e1(e1), e2(e2) {}
};

struct MultiExpr : Expr {
    Expr *e1;
    Expr *e2;

    virtual void accept(Visitor &v) {
        v.visit(this);
    }

    MultiExpr(Expr *e1, Expr *e2) : e1(e1), e2(e2) {}
};

struct DivExpr : Expr {
    Expr *e1;
    Expr *e2;

    virtual void accept(Visitor &v) {
        v.visit(this);
    }

    DivExpr(Expr *e1, Expr *e2) : e1(e1), e2(e2) {}
};

struct ModExpr : Expr {
    Expr *e1;
    Expr *e2;

    virtual void accept(Visitor &v) {
        v.visit(this);
    }

    ModExpr(Expr *e1, Expr *e2) : e1(e1), e2(e2) {}
};

struct NegExpr : Expr {
    Expr *e1;

    virtual void accept(Visitor &v) {
        v.visit(this);
    }

    NegExpr(Expr *e1) : e1(e1) {}
};

struct EqExpr : Expr {
    Expr *e1;
    Expr *e2;

    virtual void accept(Visitor &v) {
        v.visit(this);
    }

    EqExpr(Expr *e1, Expr *e2) : e1(e1), e2(e2) {}
};

struct NeqExpr : Expr {
    Expr *e1;
    Expr *e2;

    virtual void accept(Visitor &v) {
        v.visit(this);
    }

    NeqExpr(Expr *e1, Expr *e2) : e1(e1), e2(e2) {}
};

struct LeExpr : Expr {
    Expr *e1;
    Expr *e2;

    virtual void accept(Visitor &v) {
        v.visit(this);
    }

    LeExpr(Expr *e1, Expr *e2) : e1(e1), e2(e2) {}
};

struct LeqExpr : Expr {
    Expr *e1;
    Expr *e2;

    virtual void accept(Visitor &v) {
        v.visit(this);
    }

    LeqExpr(Expr *e1, Expr *e2) : e1(e1), e2(e2) {}
};

struct GeExpr : Expr {
    Expr *e1;
    Expr *e2;

    virtual void accept(Visitor &v) {
        v.visit(this);
    }

    GeExpr(Expr *e1, Expr *e2) : e1(e1), e2(e2) {}
};

struct GeqExpr : Expr {
    Expr *e1;
    Expr *e2;

    virtual void accept(Visitor &v) {
        v.visit(this);
    }

    GeqExpr(Expr *e1, Expr *e2) : e1(e1), e2(e2) {}
};

struct CondExpr : Expr {
    Expr *e1;
    Expr *e2;
    Expr *e3;

    virtual void accept(Visitor &v) {
        v.visit(this);
    }

    CondExpr(Expr *e1, Expr *e2, Expr *e3) : e1(e1), e2(e2), e3(e3) {}
};

struct AndThenExpr : Expr {
    Expr *e1;
    Expr *e2;

    virtual void accept(Visitor &v) {
        v.visit(this);
    }

    AndThenExpr(Expr *e1, Expr *e2) : e1(e1), e2(e2) {}
};

struct OrElseExpr : Expr {
    Expr *e1;
    Expr *e2;

    virtual void accept(Visitor &v) {
        v.visit(this);
    }

    OrElseExpr(Expr *e1, Expr *e2) : e1(e1), e2(e2) {}
};

struct Context {
    BoolType boolType;
    IntType intType;
};

#endif //C_AST_H
