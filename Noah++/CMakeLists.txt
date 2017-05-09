cmake_minimum_required(VERSION 3.6)
project(Noah++)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp Expr.h Eval.h Type.h Value.h Lexer.h Parser.h Stmt.h Translator.h Program.h CodeGen/CodeGen.h CodeGen/JVMCodeGen.h SymbolTable.h Symbol.h)
add_executable(C++ ${SOURCE_FILES})