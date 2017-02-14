//
// Created by noah on 2/2/17.
//

#ifndef C_EVAL_H
#define C_EVAL_H

#include "AST.h"
#include "Type.h"
#include "Value.h"

bool performEqualityOperation(Expr *e1, Expr *e2);

Value performEqualityOperation(Expr *e1, Expr *e2, std::function<bool(int, int)> func);

Value performBooleanOperation(Expr *e1, Expr *e2, std::function<bool(bool, bool)> func);

Value performIntegerOperation(Expr *e1, Expr *e2, std::function<int(int, int)> func);

Value eval(Expr *e) {
    struct V : Expr::Visitor {
        Value r;

        void visit(BoolExpr *e) {
            r.valueData = {e->val};
            r.valueType = TYPE::BoolType;
        };

        void visit(AndExpr *e) {
            r = performBooleanOperation(e->e1, e->e2, [](bool x, bool y) { return x & y; });
        };

        void visit(OrExpr *e) {
            r = performBooleanOperation(e->e1, e->e2, [](bool x, bool y) { return x | y; });
        };

        void visit(XorExpr *e) {
            r = performBooleanOperation(e->e1, e->e2, [](bool x, bool y) { return x ^ y; });
        };

        void visit(NotExpr *e) {
            r = performBooleanOperation(e->e1, e->e1, [](bool x, bool y) { return !x; });
        }

        void visit(IntExpr *e) {
            r.valueData = {e->val};
            r.valueType = TYPE::IntType;
        }

        void visit(AddExpr *e) {
            r = performIntegerOperation(e->e1, e->e2, [](int x, int y) { return x + y; });
        }

        void visit(SubExpr *e) {
            r = performIntegerOperation(e->e1, e->e2, [](int x, int y) { return x - y; });
        }

        void visit(MultiExpr *e) {
            r = performIntegerOperation(e->e1, e->e2, [](int x, int y) { return x * y; });
        }

        void visit(DivExpr *e) {
            r = performIntegerOperation(e->e1, e->e2, [](int x, int y) { return x / y; });
        }

        void visit(ModExpr *e) {
            r = performIntegerOperation(e->e1, e->e2, [](int x, int y) { return x % y; });
        }

        void visit(EqExpr *e) {
            r.valueData.boolData = performEqualityOperation(e->e1, e->e2);
            r.valueType = TYPE::BoolType;
        }

        void visit(NeqExpr *e) {
            r.valueData.boolData = !performEqualityOperation(e->e1, e->e2);
            r.valueType = TYPE::BoolType;
        }

        void visit(GeExpr *e) {
            r = performEqualityOperation(e->e1, e->e2, [](int x, int y) { return x > y; });
        }

        void visit(GeqExpr *e) {
            r = performEqualityOperation(e->e1, e->e2, [](int x, int y) { return x >= y; });
        }

        void visit(LeExpr *e) {
            r = performEqualityOperation(e->e1, e->e2, [](int x, int y) { return x < y; });
        }

        void visit(LeqExpr *e) {
            r = performEqualityOperation(e->e1, e->e2, [](int x, int y) { return x <= y; });
        }

        void visit(NegExpr *e) {
            r = performIntegerOperation(e->e1, e->e1, [](int x, int y) { return 0 - x; });
        }

        void visit(CondExpr *e) {
            r = eval(e->e1);
            if (r.valueType != TYPE::BoolType) {
                throw std::invalid_argument("Invalid arguments");
            }
            if (Type(e->e2) != Type(e->e3)) {
                throw std::invalid_argument("Invalid arguments");
            }
            r.valueData = r.valueData.boolData ? eval(e->e2).valueData : eval(e->e3).valueData;
            r.valueType = Type(e->e2);
        }
    };
    V visitor;
    e->accept(visitor);
    return visitor.r;
}

bool performEqualityOperation(Expr *e1, Expr *e2) {
    if (Type(e1) != Type(e2)) {
        throw std::invalid_argument("Invalid argument");
    }
    Value r1 = eval(e1);
    Value r2 = eval(e2);
    switch (r1.valueType) {
        case TYPE::IntType:
            return r1.valueData.intData == r2.valueData.intData;
        case TYPE::BoolType:
            return r1.valueData.boolData == r2.valueData.boolData;
        default:
            throw std::invalid_argument("Value type not yet implemented for equality");
    }
}

Value performEqualityOperation(Expr *e1, Expr *e2, std::function<bool(int, int)> func) {
    if (Type(e1) != TYPE::IntType || Type(e2) != TYPE::IntType) {
        throw std::invalid_argument("Invalid argument");
    }
    Value r;
    r.valueData = {func(eval(e1).valueData.intData, eval(e2).valueData.intData)};
    r.valueType = TYPE::IntType;
    return r;
}

Value performIntegerOperation(Expr *e1, Expr *e2, std::function<int(int, int)> func) {
    if (Type(e1) != TYPE::IntType || Type(e2) != TYPE::IntType) {
        throw std::invalid_argument("Invalid argument");
    }
    Value r;
    r.valueData = {func(eval(e1).valueData.intData, eval(e2).valueData.intData)};
    r.valueType = TYPE::IntType;
    return r;
}

Value performBooleanOperation(Expr *e1, Expr *e2, std::function<bool(bool, bool)> func) {
    if (Type(e1) != TYPE::BoolType || Type(e2) != TYPE::BoolType) {
        throw std::invalid_argument("Invalid argument");
    }
    Value r;
    r.valueData = {func(eval(e1).valueData.boolData, eval(e2).valueData.boolData)};
    r.valueType = TYPE::BoolType;
    return r;
}


#endif //C_EVAL_H
