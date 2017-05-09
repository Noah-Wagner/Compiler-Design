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
#include <fstream>
#include "Expr.h"
#include "Eval.h"
#include "assert.h"
#include "Lexer.h"
#include "Parser.h"
#include "CodeGen/CodeGen.h"
#include "CodeGen/JVMCodeGen.h"
#include "SymbolTable.h"

void CodeGenTests();

void ParseTests();

void ASTTests();

void LexerTests();

void RunTests();


void PrintTokens(const std::vector<Token *> &tokens);

void RunTestLoop();

std::string ReadFile(std::string fileName) ;

int main(int argc, char * argv[]) {

    std::string file_contents = ReadFile(argv[1]);

	std::cout << file_contents << '\n';

	SymbolTable symbol_table;

	KeywordTable keyword_table;

    std::vector<Token *> tokens = Lexer::Lexe(file_contents, symbol_table, keyword_table);

	std::vector<Stmt *> stmts;

    stmts.push_back(Parser::Parse(tokens));

    CodeGen * gen = new JVMCodeGen;
    gen->Generate(stmts);

    return 0;
}

std::string ReadFile(std::string fileName) {
    std::ifstream file(fileName);
    return std::string((std::istreambuf_iterator<char>(file)),
                       std::istreambuf_iterator<char>());
}

void RunTestLoop() {
    while (true) {
        std::string input;
        getline(std::cin, input);



	    SymbolTable symbol_table;
	    KeywordTable keyword_table;

        std::vector<Token *> tokens = Lexer::Lexe(input, symbol_table, keyword_table);

        PrintTokens(tokens);

        ExprStmt * stmt = Parser::Parse(tokens);

        Value r = eval(stmt->expr);
        std::cout << std::endl << r.valueData.intData;
        std::cout << std::endl;
    }
}

void PrintTokens(const std::vector<Token *> &tokens) {
    for (int i = 0; i < tokens.size(); i++) {
        std::cout << '<' << TokenToString(tokens[i]->kind)
                  << ((tokens[i]->attribute == "") ? "> " : ", " + tokens[i]->attribute + "> ");
    }
}


