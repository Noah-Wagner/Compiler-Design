#include <iostream>
#include "AST.h"
#include "Eval.h"

int main() {
    Context context;
    std::cout << "Hello, World!" << std::endl;
    Expr * e = new AndExpr();
    return 0;
}



