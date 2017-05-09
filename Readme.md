# Noah++
## Noah Wagner & Steven Gates - Compiler Design 

# Overview
The newest addition to this project is the implementation of code generation. This module consumes an AST root and produces JVM bytecode. The current code generator operates in a similar fashion to the previously used Eval, recursively visiting the AST in order to generate JVM instructions.

# Implementation Status

| Module                  | Status                           | Designer |
|-------------------------|----------------------------------|----------|
| Internal Representation | Implemented                      | Noah     |
| Lexical Analysis        | Implemented                      | Noah     |
| Parser                  | Implemented                      | Noah     |
| Code Generation         | Implemented, untested            | Steve    |

## Internal Representation
This language defines expression structures. These are structures that contain sub-expressions and the relationships between them. These are implemented in 'AST.h'. All expression structures inherit from a base 'Expr' class, which serves as an interface for the visitor pattern.

The language currently has two types: integer and boolean values. These are defined in 'AST.h'. Types are currently implemented with an enumeration, but this is subject to change as the demands of the internal representation grow.

All type checking is done in 'Type.h', using a visitor pattern. This is done with the 'Type(expression)' function, which recurses down the expression's AST to find the base type. This returns values from the 'TYPE' enumeration. This is subject to change.

All expression evaluations are performed in 'Eval.h'. To limit code length and increase modularity, anonymous/lambda functions were used to inject evaluation behavior into base evaluation class functions. Before evaluation, the sub-expressions are type-checked to ensure well-formed evaluation. A 'Value' structure was created in 'Value.h' to allow for multiple return types from the evaluation. This uses a discriminated union.

## Lexical Analysis
The Lexical Analyzer module consumes a sequence of characters (a string) and produces a sequence of tokens. The lexical analyzer currently supports all required operations of Noah++.

## Parser
The Parser module consumes a sequence of lexed tokens to produce an internal representation called an abstract syntax tree. The parser is implemented as a recursive descent parser, where each recursive call implements a required production. The operation precedence is implemented as specified in the homework document, matching the precedence in the C++ language. All productions have been refactored to remove infinite left recursion. The implementation of some higher end features has been completed.

## Code Generation
The Code Generation module consumes the root of an abstract syntax tree to produce JVM bytecode. The initial implementation of this is completed. This module visits the AST in post-order traversal similar to Eval.h. A singleton is made to allow a reference to a single stringstream object to persist. This object does not output to a file, but easily could be made to.
