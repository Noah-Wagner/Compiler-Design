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

#ifndef C_EVAL_H
#define C_EVAL_H

#include <cmath>
#include <functional>
#include <climits>
#include "Expr.h"
#include "Type.h"
#include "Value.h"

Value performEqualityOperation(Expr *e1, Expr *e2);

void checkType(Expr *e1, Expr *e2, TYPE type);

Value performEqualityOperation(Expr *e1, Expr *e2, std::function<bool(int, int)> func);

Value performBooleanOperation(Expr *e1, Expr *e2, std::function<bool(bool, bool)> func);

Value performIntegerOperation(Expr *e1, Expr *e2, std::function<long(long, long)> func);

Value eval(Expr *e) {
    struct V : Expr::Visitor {
        Value r;

        void visit(BoolExpr *e) {
            r.valueData = {e->val};
            r.valueType = TYPE::BoolType;
        };

        void visit(AndExpr *e) {
            r = performBooleanOperation(e->e1, e->e2, [](bool x, bool y) { return x && y; });
        };

        void visit(OrExpr *e) {
            r = performBooleanOperation(e->e1, e->e2, [](bool x, bool y) { return x || y; });
        };

		void visit(BitAndExpr * e) {
			r = performIntegerOperation(e->e1, e->e2, [](int x, int y) { return x & y; });
		};

		void visit(BitOrExpr * e) {
			r = performIntegerOperation(e->e1, e->e2, [](int x, int y) { return x | y; });
		};

        void visit(BitXorExpr * e) {
            r = performIntegerOperation(e->e1, e->e2, [](int x, int y) { return x ^ y; });
        };

        void visit(NotExpr *e) {
            r = performBooleanOperation(e->e1, e->e1, [](bool x, bool y) { return !x; });
        }

        void visit(IntExpr *e) {
            r.valueData = {e->val};
            r.valueType = TYPE::IntType;
        }

        void visit(AddExpr *e) {
            r = performIntegerOperation(e->e1, e->e2, [](long x, long y) { return x + y; });
        }

        void visit(SubExpr *e) {
            r = performIntegerOperation(e->e1, e->e2, [](long x, long y) { return x - y; });
        }

        void visit(MultiExpr *e) {
            r = performIntegerOperation(e->e1, e->e2, [](long x, long y) { return x * y; });
        }

        void visit(DivExpr *e) {
            r = performIntegerOperation(e->e1, e->e2, [](long x, long y) { return x / y; });
        }

        void visit(ModExpr *e) {
            r = performIntegerOperation(e->e1, e->e2, [](long x, long y) { return x % y; });
        }

        void visit(EqExpr *e) {
            r = performEqualityOperation(e->e1, e->e2);
        }

        void visit(NeqExpr *e) {
            r = performEqualityOperation(e->e1, e->e2);
            r.valueData = {!r.valueData.boolData};
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

        void visit(AndThenExpr *e) {
            r = eval(e->e1);
            if (r.valueType != TYPE::BoolType) {
                throw std::invalid_argument("Invalid arguments");
            }
            r.valueData = eval(e->e2).valueData;
            r.valueType = Type(e->e2);
        }

        void visit(OrElseExpr *e) {
            r.valueData = eval(e->e2).valueData;
            r.valueType = Type(e->e2);
        }
    };
    V visitor;
    e->accept(visitor);
    return visitor.r;
}

Value performEqualityOperation(Expr *e1, Expr *e2) {
    if (Type(e1) != Type(e2)) {
        throw std::invalid_argument("Invalid argument");
    }
    Value r;
    Value r1 = eval(e1);
    Value r2 = eval(e2);
    //TODO: Find a better way to do this
    switch (r1.valueType) {
        case TYPE::IntType:
            r.valueData = {r1.valueData.intData == r2.valueData.intData};
            break;
        case TYPE::BoolType:
            r.valueData = {r1.valueData.intData == r2.valueData.intData};
            break;
        default:
            throw std::invalid_argument("Value type not yet implemented for equality");
    }
    r.valueType = TYPE::BoolType;
    return r;
}

Value performEqualityOperation(Expr *e1, Expr *e2, std::function<bool(int, int)> func) {
    checkType(e1, e2, TYPE::IntType);
    Value r;
    r.valueData = {func(eval(e1).valueData.intData, eval(e2).valueData.intData)};
    r.valueType = TYPE::IntType;
    return r;
}

Value performIntegerOperation(Expr *e1, Expr *e2, std::function<long(long, long)> func) {
    checkType(e1, e2, TYPE::IntType);
    long result = func((long)eval(e1).valueData.intData, (long)eval(e2).valueData.intData);
    if (result < INT_MIN || result > INT_MAX) {
        throw std::out_of_range("Overflow");
    }
    Value r;
    r.valueData = {(int) result};
    r.valueType = TYPE::IntType;
    return r;
}

Value performBooleanOperation(Expr *e1, Expr *e2, std::function<bool(bool, bool)> func) {
    checkType(e1, e2, TYPE::BoolType);
    Value r;
    r.valueData = {func(eval(e1).valueData.boolData, eval(e2).valueData.boolData)};
    r.valueType = TYPE::BoolType;
    return r;
}

void checkType(Expr *e1, Expr *e2, TYPE type) {
    if (Type(e1) != type || Type(e2) != type) {
        throw std::invalid_argument("Invalid argument");
    }
}


#endif //C_EVAL_H
