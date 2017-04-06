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

#ifndef C_TRANSLATOR_H
#define C_TRANSLATOR_H

#include "Expr.h"
#include "Token.h"
#include "Statement.h"


struct Translator {

    ExprStmt * GetExprStmt(Expr * e1) {
        return new ExprStmt(e1);
    }

    Expr * GetAddExpr(Expr * e1, Expr * e2) {
        return new AddExpr(e1, e2);
    }

    Expr * GetSubExpr(Expr * e1, Expr * e2) {
        return new SubExpr(e1, e2);
    }

    Expr * GetMulExpr(Expr * e1, Expr * e2) {
        return new MultiExpr(e1, e2);
    }

    Expr * GetDivExpr(Expr * e1, Expr * e2) {
        return new DivExpr(e1, e2);
    }

    Expr * GetModExpr(Expr * e1, Expr * e2) {
        return new ModExpr(e1, e2);
    }

    Expr * GetNegExpr(Expr * e1) {
        return new NegExpr(e1);
    }

    Expr * GetIntExpr(Token * token) {
        return new IntExpr(std::stoi(token->attribute));
    }

    Expr * GetBoolExpr(Token * token) {
        return new BoolExpr(token->attribute == "1");
    }

    Expr * GetNotExpr(Expr * e1) {
        return new NotExpr(e1);
    }

	Expr * GetLtExpr(Expr * e1, Expr * e2) {
		return new LeExpr(e1, e2);
	}

	Expr * GetLtEqExpr(Expr * e1, Expr * e2) {
		return new LeqExpr(e1, e2);
	}

	Expr * GetGtExpr(Expr * e1, Expr * e2) {
		return new GeExpr(e1, e2);
	}

	Expr * GetGtEqExpr(Expr * e1, Expr * e2) {
		return new GeqExpr(e1, e2);
	}

	Expr * GetEqExpr(Expr * e1, Expr * e2) {
		return new EqExpr(e1, e2);
	}

	Expr * GetNeqExpr(Expr * e1, Expr * e2) {
		return new NeqExpr(e1, e2);
	}

	Expr * GetAndExpr(Expr * e1, Expr * e2) {
		return new AndExpr(e1, e2);
	}

	Expr * GetOrExpr(Expr * e1, Expr * e2) {
		return new OrExpr(e1, e2);
	}

	Expr * GetBitAndExpr(Expr * e1, Expr * e2) {
		return new BitAndExpr(e1, e2);
	}

	Expr * GetBitOrExpr(Expr * e1, Expr * e2) {
		return new BitOrExpr(e1, e2);
	}

	Expr * GetBitXorExpr(Expr * e1, Expr * e2) {
		return new BitXorExpr(e1, e2);
	}


};

#endif //C_TRANSLATOR_H
