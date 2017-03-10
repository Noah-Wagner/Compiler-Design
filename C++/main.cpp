#include <iostream>
#include <vector>
#include "AST.h"
#include "Eval.h"
#include "assert.h"
#include "Lexer.h"

void RunTests();

void ASTTests();

void LexerTests();

std::vector<Token *> GetTokenSequence(std::string);

int main() {
    RunTests();
    return 0;
}

void RunTests() {

    ASTTests();

    LexerTests();


}

void LexerTests() {
    std::vector<Token *> tokens;

    tokens = GetTokenSequence("364565 + 12345 - 5555 * 456 / 65");
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

    tokens = GetTokenSequence("!true");
    assert(tokens[0]->kind == TOKEN_KIND::NotTok);
    assert(tokens[1]->kind == TOKEN_KIND::BoolTok);
    assert(tokens[1]->attribute == "1");

    tokens = GetTokenSequence("true || false");
    assert(tokens[0]->kind == TOKEN_KIND::BoolTok);
    assert(tokens[0]->attribute == "1");
    assert(tokens[1]->kind == TOKEN_KIND::OrTok);
    assert(tokens[2]->kind == TOKEN_KIND::BoolTok);
    assert(tokens[2]->attribute == "0");

    bool exceptionThrown = false;
    try {
        tokens = GetTokenSequence("asdf");
    } catch (...) {
        exceptionThrown = true;
    }
    assert(exceptionThrown);
}

std::vector<Token *> GetTokenSequence(std::string input) {
    std::vector<Token *> tokens;
    Token *token;
    Lexer lexer(input);
    while (!lexer.IsEof()) {
        token = lexer.Next();
        tokens.push_back(token);
    }
    token = lexer.Next();
    tokens.push_back(token);
    return tokens;
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
