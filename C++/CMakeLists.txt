cmake_minimum_required(VERSION 3.6)
project(C++)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp Expr.h Eval.h Type.h Value.h Lexer.h Parser.h Statement.h Translator.h Program.h)
add_executable(C++ ${SOURCE_FILES})