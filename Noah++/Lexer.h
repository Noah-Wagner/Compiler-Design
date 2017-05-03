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
#include <iostream>
#include <vector>
#include "Eval.h"
#include "Token.h"

struct Lexer {
	const char * first;
	const char * last;
	std::string buffer;

	Lexer() {
		ClearBuffer();
		const char * first = NULL;
		const char * last = NULL;
	}

	std::string ProcessString(const std::string &basic_string);

	Lexer(const std::string &parseString) {
//		std::string str = ProcessString(parseString);
		first = &parseString[0];
		last = &parseString[parseString.length() - 1];
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

	static std::vector<Token *> Lexe(std::string input) {
		std::vector<Token *> tokens;
		Token * token;
		Lexer lexer(input);
		while (!lexer.IsEof()) {
			token = lexer.Next();
			tokens.push_back(token);
		}
		token = lexer.Next();
		tokens.push_back(token);
		return tokens;
	}

};

Token * Lexer::Next() {
	std::string temp;

	if (LookAhead() == '#') {
		Comment();
		temp = buffer.substr(1);
		ClearBuffer();
		return new Token(TOKEN_KIND::CommTok, temp);
	}

	char lookAhead = LookAhead();
	Consume();

	switch (lookAhead) {
		case 0:
			ClearBuffer();
			return new Token(TOKEN_KIND::EOFTok);
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
				return new Token(TOKEN_KIND::AndTok);
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
				Consume();
				ClearBuffer();
				return new Token(TOKEN_KIND::NeqTok);
			}
			ClearBuffer();
			return new Token(TOKEN_KIND::NotTok);
		case '=':
			if (LookAhead() == '=') {
				Consume();
				ClearBuffer();
				return new Token(TOKEN_KIND::EqTok);
			}
			throw std::invalid_argument("Unsupported syntax");
		case '<':
			if (LookAhead() == '=') {
				Consume();
				ClearBuffer();
				return new Token(TOKEN_KIND::LtEqTok);
			}
			if (LookAhead() == '<') {
				Consume();
				ClearBuffer();
				return new Token(TOKEN_KIND::BitLeftTok);
			}
			ClearBuffer();
			return new Token(TOKEN_KIND::LtTok);
		case '>':
			if (LookAhead() == '=') {
				Consume();
				ClearBuffer();
				return new Token(TOKEN_KIND::GtEqTok);
			}
			if (LookAhead() == '>') {
				Consume();
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
        case ';':
            ClearBuffer();
            return new Token(TOKEN_KIND::SemiColTok);
		case '(':
			ClearBuffer();
			return new Token(TOKEN_KIND::LeftParenTok);
		case ')':
			ClearBuffer();
			return new Token(TOKEN_KIND::RightParenTok);
		case '^':
			ClearBuffer();
			return new Token(TOKEN_KIND::BitXorTok);
        case 'i':
            if (LookAhead() == 'n') {
                Consume();
                if (LookAhead() == 't') {
                    Consume();
                    ClearBuffer();
                    return new Token(TOKEN_KIND::VarIntTok);
                }
            }
            throw std::invalid_argument("Unsupported syntax");
        case 'b':
            if (LookAhead() == 'o') {
                Consume();
                if (LookAhead() == 'o') {
                    Consume();
                    if (LookAhead() == 'l') {
                        Consume();
                        ClearBuffer();
                        return new Token(TOKEN_KIND::VarBoolTok);
                    }
                }
            }
            throw std::invalid_argument("Unsupported syntax");
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
			if (LookAhead() == 'b') {
				Consume();
				ClearBuffer();
				while (std::isdigit(LookAhead())) {
					Consume();
				}
				std::string bufferStore = buffer;
				ClearBuffer();
				return new Token(TOKEN_KIND::IntTok, std::stoi(bufferStore, nullptr, 2));
			}
			if (LookAhead() == 'x') {
				Consume();
				ClearBuffer();
				while (std::isxdigit(LookAhead())) {
					Consume();
				}
				std::string bufferStore = buffer;
				ClearBuffer();
				return new Token(TOKEN_KIND::IntTok, std::stoi(bufferStore, nullptr, 16));
			}
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
			std::string bufferStore = buffer;
			ClearBuffer();
			return new Token(TOKEN_KIND::IntTok, bufferStore);

	}

	throw std::invalid_argument("Unsupported syntax");

}

std::string Lexer::ProcessString(const std::string &basic_string) {
	std::string str(basic_string);
	size_t first = str.find_first_not_of(' ');
	if (std::string::npos == first)
	{
		return str;
	}
	size_t last = str.find_last_not_of(' ');
	return str.substr(first, (last - first + 1)) + ' ';
}


#endif //C_LEXER_H