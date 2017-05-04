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

#ifndef C_TOKEN_H
#define C_TOKEN_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include "Eval.h"

enum TOKEN_KIND {

	EOFTok, AddTok,
	SubTok, MulTok,
	DivTok, ModTok,
	AndTok, OrTok,
	NotTok, EqTok,
	NeqTok, LtTok,
	GtTok,  LtEqTok,
	GtEqTok, QuTok,
	ColonTok, LeftParenTok,
	RightParenTok, IntTok,
	BoolTok, CommTok,
	BitLeftTok, BitRightTok,
	BitXorTok,
	BitAndTok, BitOrTok,

	VarIntTok, VarBoolTok,

	SemiColTok,

	VarNameTok,



	TrueKw, FalseKw,
	VarKw, IntKw,
	ReturnKw, DefKw,
	BoolKw


};

struct Token {

	TOKEN_KIND kind;
	std::string attribute;

	Token() {}

	Token(TOKEN_KIND kind)
			: kind(kind) {}

	Token(TOKEN_KIND kind, int attr)
			: kind(kind), attribute(std::to_string(attr)) {}

	Token(TOKEN_KIND kind, std::string str)
			: kind(kind), attribute(str) {}

};

std::string TokenToString(TOKEN_KIND token) {
	switch (token) {

		case EOFTok: return "0/";
		case AddTok: return "+";
		case SubTok: return "-";
		case MulTok: return "*";
		case DivTok: return "/";
		case ModTok: return "%";
		case AndTok: return "&&";
		case OrTok: return "||";
		case NotTok: return "!";
		case EqTok: return "==";
		case NeqTok: return "!=";
		case LtTok: return "<";
		case GtTok: return ">";
		case LtEqTok: return "<=";
		case GtEqTok: return ">=";
		case QuTok: return "?";
		case ColonTok: return ":";
		case LeftParenTok: return "(";
		case RightParenTok: return ")";
		case IntTok: return "INT";
		case BoolTok: return "BOOL";
		case CommTok: return "#";
		case BitLeftTok: return "<<";
		case BitRightTok: return ">>";
		case BitXorTok: return "^";
		case BitAndTok: return "&";
		case BitOrTok: return "|";
	}
}


struct KeywordTable : std::unordered_map<std::string, TOKEN_KIND > {

	KeywordTable() {
		insert({"true", TrueKw});
		insert({"def", DefKw});
		insert({"false", FalseKw});
		insert({"int", IntKw});
		insert({"bool", BoolKw});
		insert({"return", ReturnKw});
		insert({"var", VarKw});
	}



};



#endif //C_TOKEN_H
