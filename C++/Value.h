//
// Created by Noah Wagner on 2/2/17.
//

#ifndef C_VALUE_H
#define C_VALUE_H
#include "AST.h"

struct Value {

    union ValueData {
        int intData;
        bool boolData;
    };

    TYPE valueType;
    ValueData valueData;
};

#endif //C_VALUE_H
