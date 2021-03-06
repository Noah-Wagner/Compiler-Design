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
#include "SymbolTable.h"
#include "Symbol.h"

struct Lexer {
	const char * first;
	const char * last;
	std::string buffer;
	KeywordTable * keyword_table;
	SymbolTable  * symbol_table;

//	Lexer() {
//		ClearBuffer();
//		const char * first = NULL;
//		const char * last = NULL;
//	}

	std::string ProcessString(const std::string &basic_string);

	Lexer(const std::string & parseString, SymbolTable & symbol_table, KeywordTable & keyword_table) :
			keyword_table(&keyword_table), symbol_table(&symbol_table) {

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

	static std::vector<Token *> Lexe(std::string input, SymbolTable & symbol_table, KeywordTable & keyword_table) {
		Lexer lexer(input, symbol_table, keyword_table);
		std::vector<Token *> tokens;
		Token * token;
		while (!lexer.IsEof()) {
			token = lexer.Next();
			tokens.push_back(token);
		}
		token = lexer.Next();
		tokens.push_back(token);
		return tokens;
	}

	Token * ConsumeWord();

	Token * ConsumeNum();
};

bool IsAlpha(const char & c);

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
			ClearBuffer();
			return new Token(TOKEN_KIND::AssignTok);
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


		default:
			if (IsAlpha(lookAhead)) {
				return ConsumeWord();
			} else if (std::isdigit(lookAhead)) {
				return ConsumeNum();
			}

	}

	throw std::invalid_argument("Unsupported syntax");

}

Token * Lexer::ConsumeWord() {
	while (IsAlpha(LookAhead())) {
		Consume();
	}
	auto iter = keyword_table->find(buffer);
	if (iter != keyword_table->end()) {
		ClearBuffer();
		return new Token(iter->second);
	} else { // Token ID
		const std::string * symbol = symbol_table->insert(buffer);
		return new Token(TOKEN_KIND::IdTok, *symbol);
	}
}

Token * Lexer::ConsumeNum() {
	while (std::isdigit(LookAhead())) {
		Consume();
	}
	std::string bufferStore = buffer;
	ClearBuffer();
	return new Token(TOKEN_KIND::IntTok, std::stoi(bufferStore));
}

bool IsAlpha(const char & c) {
	return std::isalpha(c) || c == '_';
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
