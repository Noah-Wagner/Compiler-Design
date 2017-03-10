#Noah Wagner - Compiler Design 
#Homework 2
###Calculator Application

#Overview
The new addition to this project is the implementation of a lexical analyzer. The lexical analyzer parses through a sequence of characters to produce a sequence of tokens. While not yet internal syntax, this is an important first step in the front-end of our compilers.

#Implementation
##Lexer
The lexer has 27 valid tokens, as outlined by the 'TOKEN_KIND' enum. Each token contains two fields: the 'TOKEN_KIND' and the optional 'attribute'. This optional 'attribute' can be things such as the integer value of an 'IntToken'.

The main routine is powered by the 'Lexer' struct. Each 'Lexer' is instantiated on a string, and contains char pointers to the tail and head of the string. The important methods of the 'Lexer' class are LookAhead, Next, and Consume. LookAhead simply returns the next character from the input hcaracter sequence. Consume will append the next character to a string buffer and advance the first pointer. Next will process the next character and create a resulting token based on its character representation. White-space is ignored.
