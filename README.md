--------------
#Compiler Design - Homework 1
##Noah Wagner
###Internal representation of a small expression language 

#Overview
This code currently supports the internal representation of a small expression language as defined in the Homework 1 specification. This is the beginnings of a compiler, with no parsing or front end yet implemented. The atomic unit of this language is the expression, a recursive structure that delineates relationships between sub-expressions. At the bottom of any AST are the primitive types, currently comprised of the integer type and the boolean type. The code in the current state supports arithmetic bounds checking, type checking, and recursive expression evaluation. The visitor pattern is used for readability and to promote future extensibility. 

#Implementation

This language defines expression structures. These are structures that contain sub-expressions and the relationships between them. These are implemented in 'AST.h'. All expression structures inherit from a base 'Expr' class, which serves as an interface for the visitor pattern.

The language currently has two types: integer and boolean values. These are defined in 'AST.h'. Types are currently implemented with an enumeration, but this is subject to change as the demands of the internal representation grow. 

All type checking is done in 'Type.h', using a visitor pattern. This is done with the 'Type(expression)' function, which recurses down the expression's AST to find the base type. This returns values from the 'TYPE' enumeration. This is subject to change.

All expression evaluations are performed in 'Eval.h'. To limit code length and increase modularity, anonymous/lambda functions were used to inject evaluation behavior into base evaluation class functions. Before evaluation, the sub-expressions are type-checked to ensure well-formed evaluation. A 'Value' structure was created in 'Value.h' to allow for multiple return types from the evaluation. This uses a discriminated union.


