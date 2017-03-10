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

#ifndef C_LEXER_H
#define C_LEXER_H

#include <string>

enum class TOKEN_KIND {
    EOFTok, AddTok,
    SubTok, MulTok,
    DivTok, ModTok,
    AmpTok, OrTok,
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
    std::string attribute;

    Token() {}

    Token(TOKEN_KIND kind)
            : kind(kind) {}

    Token(TOKEN_KIND kind, int attr)
            : kind(kind), attribute(std::to_string(attr)) {}

    Token(TOKEN_KIND kind, std::string str)
            : kind(kind), attribute(str) {}

};

struct Lexer {
    const char * first;
    const char * last;
    std::string buffer;

    Lexer() {
        ClearBuffer();
        const char * first = NULL;
        const char * last = NULL;
    }

    Lexer(const std::string & str) {
        first = &str[0];
        last = &str[str.length() - 1];
    }

    bool IsEof() {
        return first == last || *first == 0;
    }

    char LookAhead() const {
        return *first;
    }

    void Consume() {
        buffer += *first++;
    }

    void Comment() {
        while (first != last) {
            Consume();
        }
        Consume();
    }

    void ClearBuffer() {
        buffer = "";
    }

    Token * Next();
};

Token * Lexer::Next() {
    std::string temp;

    if (LookAhead() == '#') {
        Comment();
        temp = buffer.substr(1);
        ClearBuffer();
        return new Token(TOKEN_KIND::CommTok, temp);
    }

    if (IsEof()) {
        ClearBuffer();
        return new Token(TOKEN_KIND::EOFTok);
    }

    char test = LookAhead();
    Consume();

    switch (test) {
        case ' ':
            ClearBuffer();
            return Next();
        case '+':
            ClearBuffer();
            return new Token(TOKEN_KIND::AddTok);
        case '-':
            ClearBuffer();
            return new Token(TOKEN_KIND::SubTok);
        case '*':
            ClearBuffer();
            return new Token(TOKEN_KIND::MulTok);
        case '/':
            ClearBuffer();
            return new Token(TOKEN_KIND::DivTok);
        case '%':
            ClearBuffer();
            return new Token(TOKEN_KIND::ModTok);
        case '&':
            if (LookAhead() == '&') {
                Consume();
                ClearBuffer();
                return new Token(TOKEN_KIND::AmpTok);
            }
            ClearBuffer();
            return new Token(TOKEN_KIND::BitAndTok);
        case '|':
            if (LookAhead() == '|') {
                Consume();
                ClearBuffer();
                return new Token(TOKEN_KIND::OrTok);
            }
            ClearBuffer();
            return new Token(TOKEN_KIND::BitOrTok);
        case '!':
            if (LookAhead() == '=') {
                ClearBuffer();
                return new Token(TOKEN_KIND::NeqTok);
            }
            ClearBuffer();
            return new Token(TOKEN_KIND::NotTok);
        case '=':
            if (LookAhead() == '=') {
                ClearBuffer();
                return new Token(TOKEN_KIND::EqTok);
            }
            throw std::invalid_argument("Unsupported syntax");
        case '<':
            if (LookAhead() == '=') {
                ClearBuffer();
                return new Token(TOKEN_KIND::LtEqTok);
            }
            if (LookAhead() == '<') {
                ClearBuffer();
                return new Token(TOKEN_KIND::BitLeftTok);
            }
            ClearBuffer();
            return new Token(TOKEN_KIND::LtTok);
        case '>':
            if (LookAhead() == '=') {
                ClearBuffer();
                return new Token(TOKEN_KIND::GtEqTok);
            }
            if (LookAhead() == '>') {
                ClearBuffer();
                return new Token(TOKEN_KIND::BitRightTok);
            }
            ClearBuffer();
            return new Token(TOKEN_KIND::GtTok);
        case '?':
            ClearBuffer();
            return new Token(TOKEN_KIND::QuTok);
        case ':':
            ClearBuffer();
            return new Token(TOKEN_KIND::ColonTok);
        case '(':
            ClearBuffer();
            return new Token(TOKEN_KIND::LeftParenTok);
        case ')':
            ClearBuffer();
            return new Token(TOKEN_KIND::RightParenTok);
        case '^':
            ClearBuffer();
            return new Token(TOKEN_KIND::XorTok);
        case 't':
            if (LookAhead() == 'r') {
                Consume();
                if (LookAhead() == 'u') {
                    Consume();
                    if (LookAhead() == 'e') {
                        Consume();
                        ClearBuffer();
                        return new Token(TOKEN_KIND::BoolTok, 1);
                    }
                }
            }
            throw std::invalid_argument("Unsupported syntax");
        case 'f':
            if (LookAhead() == 'a') {
                Consume();
                if (LookAhead() == 'l') {
                    Consume();
                    if (LookAhead() == 's') {
                        Consume();
                        if (LookAhead() == 'e') {
                            Consume();
                            ClearBuffer();
                            return new Token(TOKEN_KIND::BoolTok, 0);
                        }
                    }
                }
            }
            throw std::invalid_argument("Unsupported syntax");
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            while (std::isdigit(LookAhead())) {
                Consume();
            }
            std::string test = buffer;
            ClearBuffer();
            return new Token(TOKEN_KIND::IntTok, test);

    }
    throw std::invalid_argument("Unsupported syntax");

}


#endif //C_LEXER_H
