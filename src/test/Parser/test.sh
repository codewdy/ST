#!/bin/sh
rm *.o
cd ../../Parser
flex Lexer.l
lemon Parser.y
cd ../test/Parser
g++ -std=c++11 -I ../../Include  *.cpp -c 
g++ -std=c++11 -I ../../Include  ../../AST/*.cpp -c 
g++ -std=c++11 -I ../../Include  ../../Parser/Lexer.cpp ../../Parser/Parser.c -c 
g++ *.o -o test
./test

