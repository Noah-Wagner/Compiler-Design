//
// Created by Noah Wagner on 2/2/17.
//

#ifndef C_VALUE_H
#define C_VALUE_H

enum class VALUE_TYPE {
    Int_Type,
    Bool_Type,
};

union Value_Data {
    int intData;
    bool boolData;
};

struct Value {
    VALUE_TYPE valueType;
    Value_Data valueData;
};

#endif //C_VALUE_H
