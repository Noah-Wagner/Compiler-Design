//
// Created by Noah Wagner on 2/2/17.
//

#ifndef C_VALUE_H
#define C_VALUE_H
#include "AST.h"

struct Value {

    union Value_Data {
        int intData;
        bool boolData;
    };

    TYPE valueType;
    Value_Data valueData;
};

#endif //C_VALUE_H
