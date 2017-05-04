//
// Created by Noah on 3/May/2017.
//

#ifndef NOAH_CODEGEN_H
#define NOAH_CODEGEN_H

#include "../Stmt.h"

struct CodeGen {

public:

    virtual void Generate(Stmt *) = 0;

};

#endif //NOAH_CODEGEN_H
