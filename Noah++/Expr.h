/*
 * Copyright (c) 2017 Noah Wagner.
 *
 * This program is free software: you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation, either version 3 of the License, or
 *     (at your option) any later version.
 *
 *     This program is distributed in the hope that it will be useful,
 *     but WITHOUT ANY WARRANTY; without even the implied warranty of
 *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *     GNU General Public License for more details.
 *
 *     You should have received a copy of the GNU General Public License
 *     along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef C_AST_H
#define C_AST_H

struct BoolType;
struct IntType;

struct BoolExpr;
struct AndExpr;
struct OrExpr;
struct NotExpr;

struct BitAndExpr;
struct BitOrExpr;
struct BitXorExpr;

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

struct Expr {
    virtual ~Expr() = default;

    struct Visitor;

    virtual void accept(Expr::Visitor &) = 0;
};


struct Expr::Visitor {
    virtual void visit(BoolExpr *) = 0;

    virtual void visit(AndExpr *) = 0;

    virtual void visit(OrExpr *) = 0;

	virtual void visit(BitAndExpr *) = 0;

	virtual void visit(BitOrExpr *) = 0;

    virtual void visit(BitXorExpr *) = 0;

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

struct BitAndExpr : Expr {
	Expr *e1;
	Expr *e2;

	virtual void accept(Visitor &v) {
		v.visit(this);
	}

	BitAndExpr(Expr *e1, Expr *e2) : e1(e1), e2(e2) {}
};

struct BitOrExpr : Expr {
	Expr *e1;
	Expr *e2;

	virtual void accept(Visitor &v) {
		v.visit(this);
	}

	BitOrExpr(Expr *e1, Expr *e2) : e1(e1), e2(e2) {}
};

struct BitXorExpr : Expr {
    Expr *e1;
    Expr *e2;

    virtual void accept(Visitor &v) {
        v.visit(this);
    }

    BitXorExpr(Expr *e1, Expr *e2) : e1(e1), e2(e2) {}
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


#endif //C_AST_H
