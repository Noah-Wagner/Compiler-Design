#include <iostream>
#include "AST.h"
#include "Eval.h"
#include "assert.h"

void runTests();

int main() {
    runTests();
    return 0;
}

void runTests() {

    Expr * e = new AddExpr(new IntExpr(3), new IntExpr(5));
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
