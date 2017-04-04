//
// Created by Noah Wagner on 4/3/17.
//

#ifndef C_TOKEN_H
#define C_TOKEN_H

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
    XorTok,
    BitAndTok, BitOrTok
};

struct Token {

    TOKEN_KIND kind;
    std::__1::string attribute;

    Token() {}

    Token(TOKEN_KIND kind)
            : kind(kind) {}

    Token(TOKEN_KIND kind, int attr)
            : kind(kind), attribute(std::to_string(attr)) {}

    Token(TOKEN_KIND kind, std::__1::string str)
            : kind(kind), attribute(str) {}

};

std::__1::string TokenToString(TOKEN_KIND token) {
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
        case XorTok: return "^";
        case BitAndTok: return "&";
        case BitOrTok: return "|";
    }
}

#include <iostream>
#include <vector>
#include "Eval.h"

#endif //C_TOKEN_H
