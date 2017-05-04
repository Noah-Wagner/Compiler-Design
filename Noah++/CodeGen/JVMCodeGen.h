//
// Created by Noah on 3/May/2017.
//

#ifndef NOAH_JVMCODEGEN_H
#define NOAH_JVMCODEGEN_H

#include <iostream>
#include "CodeGen.h"

struct JVMCodeGen : CodeGen {

public:

    virtual void Generate(Stmt * stmt) {
        std::cout << "testxd";
    }

};

#endif //NOAH_JVMCODEGEN_H
