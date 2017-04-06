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

#include <iostream>
#include <vector>
#include "Expr.h"
#include "Eval.h"
#include "assert.h"
#include "Lexer.h"
#include "Parser.h"

void RunTests();

void ParseTests();

void ASTTests();

void LexerTests();

int main() {
    RunTests();

    while (true) {
        std::string input;
        std::getline(std::cin, input);

        std::vector<Token *> tokens = Lexer::Lexe(input);

        ExprStmt * stmt = Parser::Parse(tokens);

        for (int i = 0; i < tokens.size(); i++) {
            std::cout << '<' << TokenToString(tokens[i]->kind)
                      << ((tokens[i]->attribute == "") ? "> " : ", " + tokens[i]->attribute + "> ");
        }
        Value r = eval(stmt->expr);
        std::cout << std::endl << r.valueData.intData;
        std::cout << std::endl;
    }

    return 0;
}

void RunTests() {
    ParseTests();
    ASTTests();
    LexerTests();
    std::cout << "Tests passed\n";
}

void ParseTests() {
    std::vector<Token *> tokens;

    tokens = Lexer::Lexe("4 + 5");

    ExprStmt * stmt = Parser::Parse(tokens);

    assert(eval(stmt->expr).valueData.intData == 9);

    stmt = Parser::Parse("4 - 6");
    assert(eval(stmt->expr).valueData.intData == -2);

    stmt = Parser::Parse("23 * 2");
    assert(eval(stmt->expr).valueData.intData == 46);

    stmt = Parser::Parse("23 * -2");
    assert(eval(stmt->expr).valueData.intData == -46);

    stmt = Parser::Parse("24 / 12");
    assert(eval(stmt->expr).valueData.intData == 2);

    stmt = Parser::Parse("25 % 3");
    assert(eval(stmt->expr).valueData.intData == 1);

    stmt = Parser::Parse("14 + 3 * 2");
    assert(eval(stmt->expr).valueData.intData == 20);

    stmt = Parser::Parse("14 + 3 * 2 * 2");
    assert(eval(stmt->expr).valueData.intData == 26);

    stmt = Parser::Parse("14 + 3 * 2 * 2 / 2");
    assert(eval(stmt->expr).valueData.intData == 20);

    stmt = Parser::Parse("true");
    assert(eval(stmt->expr).valueData.boolData);

    stmt = Parser::Parse("false");
    assert(!eval(stmt->expr).valueData.boolData);

    stmt = Parser::Parse("!false");
    assert(eval(stmt->expr).valueData.boolData);

    stmt = Parser::Parse("!true");
    assert(!eval(stmt->expr).valueData.boolData);

	stmt = Parser::Parse("!true && false");
	assert(!eval(stmt->expr).valueData.boolData);

	stmt = Parser::Parse("!false && true");
	assert(eval(stmt->expr).valueData.boolData);

	stmt = Parser::Parse("true || true && false");
	assert(eval(stmt->expr).valueData.boolData);

	stmt = Parser::Parse("#comment test");

	stmt = Parser::Parse("3 || 5");
	assert(eval(stmt->expr).valueData.boolData == 1);

	stmt = Parser::Parse("3 | 4");
	assert(eval(stmt->expr).valueData.intData == 7);

	stmt = Parser::Parse("3 & 7");
	assert(eval(stmt->expr).valueData.intData == 3);

	stmt = Parser::Parse("3 < 7");
	assert(eval(stmt->expr).valueData.boolData);

	stmt = Parser::Parse("3 <= 7");
	assert(eval(stmt->expr).valueData.boolData);

	stmt = Parser::Parse("4 <= 3");
	assert(!eval(stmt->expr).valueData.boolData);

	stmt = Parser::Parse("4 > 3");
	assert(eval(stmt->expr).valueData.boolData);

	stmt = Parser::Parse("4 >= 4");
	assert(eval(stmt->expr).valueData.boolData);

	stmt = Parser::Parse("3 >= 4");
	assert(!eval(stmt->expr).valueData.boolData);

	stmt = Parser::Parse("0b10 + 0b10");
	assert(eval(stmt->expr).valueData.intData == 0b10 + 0b10);

	stmt = Parser::Parse("0b11 * 0b10");
	assert(eval(stmt->expr).valueData.intData == 0b11 * 0b10);

	stmt = Parser::Parse("0xA1 * 0xAB");
	assert(eval(stmt->expr).valueData.intData == 0xA1 * 0xAB);


}

void LexerTests() {
    std::vector<Token *> tokens;

    tokens = Lexer::Lexe("4 + 5");
    assert(tokens[0]->kind == TOKEN_KIND::IntTok);
    assert(tokens[0]->attribute == "4");
    assert(tokens[1]->kind == TOKEN_KIND::AddTok);
    assert(tokens[2]->kind == TOKEN_KIND::IntTok);
    assert(tokens[2]->attribute == "5");

    tokens = Lexer::Lexe("364565 + 12345 - 5555 * 456 / 65");
    assert(tokens[0]->kind == TOKEN_KIND::IntTok);
    assert(tokens[0]->attribute == "364565");
    assert(tokens[1]->kind == TOKEN_KIND::AddTok);
    assert(tokens[2]->kind == TOKEN_KIND::IntTok);
    assert(tokens[2]->attribute == "12345");
    assert(tokens[3]->kind == TOKEN_KIND::SubTok);
    assert(tokens[4]->kind == TOKEN_KIND::IntTok);
    assert(tokens[4]->attribute == "5555");
    assert(tokens[5]->kind == TOKEN_KIND::MulTok);
    assert(tokens[6]->kind == TOKEN_KIND::IntTok);
    assert(tokens[6]->attribute == "456");
    assert(tokens[7]->kind == TOKEN_KIND::DivTok);
    assert(tokens[8]->kind == TOKEN_KIND::IntTok);
    assert(tokens[8]->attribute == "65");

    tokens = Lexer::Lexe("3 <= 4");
    tokens = Lexer::Lexe("3 >= 4");
    tokens = Lexer::Lexe("3 == 3");
    tokens = Lexer::Lexe("3 != 4");

    tokens = Lexer::Lexe("!true");
    assert(tokens[0]->kind == TOKEN_KIND::NotTok);
    assert(tokens[1]->kind == TOKEN_KIND::BoolTok);
    assert(tokens[1]->attribute == "1");

    tokens = Lexer::Lexe("true || false");
    assert(tokens[0]->kind == TOKEN_KIND::BoolTok);
    assert(tokens[0]->attribute == "1");
    assert(tokens[1]->kind == TOKEN_KIND::OrTok);
    assert(tokens[2]->kind == TOKEN_KIND::BoolTok);
    assert(tokens[2]->attribute == "0");

    tokens = Lexer::Lexe("#test");
    assert(tokens[0]->kind == TOKEN_KIND::CommTok);
    assert(tokens[0]->attribute == "test");

    bool exceptionThrown = false;
    try {
        tokens = Lexer::Lexe("asdf");
    } catch (...) {
        exceptionThrown = true;
    }
    assert(exceptionThrown);
}

void ASTTests() {

    Expr *e = new AddExpr(new IntExpr(3), new IntExpr(5));
    assert(eval(e).valueData.intData == 8);

    e = new AddExpr(new MultiExpr(new IntExpr(3), new IntExpr(4)), new IntExpr(7));
    assert(eval(e).valueData.intData == 19);

    e = new SubExpr(new IntExpr(7), new IntExpr(3));
    assert(eval(e).valueData.intData == 4);

    e = new MultiExpr(new IntExpr(3), new IntExpr(41));
    assert(eval(e).valueData.intData == 123);

    e = new DivExpr(new IntExpr(7), new IntExpr(3));
    assert(eval(e).valueData.intData == 2);

    e = new ModExpr(new IntExpr(7), new IntExpr(3));
    assert(eval(e).valueData.intData == 1);

    e = new AndExpr(new BoolExpr(true), new BoolExpr(false));
    assert(eval(e).valueData.boolData == false);

    e = new OrExpr(new BoolExpr(true), new BoolExpr(false));
    assert(eval(e).valueData.boolData == true);

    e = new NotExpr(new BoolExpr(true));
    assert(eval(e).valueData.boolData == false);

    e = new GeExpr(new IntExpr(4), new IntExpr(4));
    assert(eval(e).valueData.boolData == false);

    e = new GeqExpr(new IntExpr(4), new IntExpr(4));
    assert(eval(e).valueData.boolData == true);

    e = new LeExpr(new IntExpr(2), new IntExpr(9));
    assert(eval(e).valueData.boolData == true);

    e = new LeqExpr(new IntExpr(7), new IntExpr(3));
    assert(eval(e).valueData.boolData == false);

    e = new NegExpr(new IntExpr(-3));
    assert(eval(e).valueData.intData == 3);

    e = new BoolExpr(3);
    assert(eval(e).valueData.boolData == true);

    e = new CondExpr(new BoolExpr(false), new IntExpr(4), new IntExpr(7));
    assert(eval(e).valueData.intData == 7);

    e = new CondExpr(new BoolExpr(true), new IntExpr(4), new IntExpr(7));
    assert(eval(e).valueData.intData == 4);

    bool exceptionThrown = false;
    try {
        e = new AddExpr(new IntExpr(-1), new IntExpr(INT_MIN));
        std::cout << eval(e).valueData.intData;
    } catch (...) {
        exceptionThrown = true;
    }
    assert(exceptionThrown);

}
