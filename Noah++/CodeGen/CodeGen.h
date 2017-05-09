//
// Created by Steve on 1/May/2017.
//

#ifndef STEVE_CODEGEN_H
#define STEVE_CODEGEN_H

#include "../Stmt.h"

struct CodeGen {

public:

    virtual void Generate(std::vector<Stmt *> ) = 0;

};

#endif //STEVE_CODEGEN_H
