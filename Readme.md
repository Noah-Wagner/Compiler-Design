# Noah Wagner - Compiler Design 
# Homework 3
### Noah++

# Overview
The newest addition to this project is the implementation of a parser. The parser traverses through a sequence of tokens (provided by previously implemented lexical analyzer) to produce an AST. This means that the front-end of the compiler is now functional, parsing and correctly translating concretely written commands to internal syntax.

# Implementation
## Parser
The input to the parser is a sequence of tokens. The parser is implemented as a recursive descent parser, where each recursive call implements a required production. The operation precedence is implemented as specified in the homework document, matching the precedence in the C++ language. After the AST is constructed, it is wrapped as a statement to be used in a later homework. 
