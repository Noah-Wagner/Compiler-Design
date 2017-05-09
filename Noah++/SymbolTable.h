//
// Created by Noah on 4/May/2017.
//

#ifndef NOAH_SYMBOLTABLE_H
#define NOAH_SYMBOLTABLE_H

#include <unordered_map>

struct SymbolTable {

	using Symbol = std::string;

public:

	const Symbol * insert(const std::string & symbol) {
		auto iter = map.insert({symbol, nullptr});
		return &iter.first->first;
	}

	const Symbol * find(const std::string & str) {
		auto iter = map.find(str);
		return &iter->first;
	}

private:

	std::unordered_map<Symbol, void *> map;

};

#endif //NOAH_SYMBOLTABLE_H
