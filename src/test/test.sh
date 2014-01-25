#!/bin/sh
rm *.o
cd ../Parser
flex Lexer.l
lemon Parser.y
cd ../test
g++ -g -std=c++11 -I ../Include  *.cpp -c 
g++ -g -std=c++11 -I ../Include  ../AST/*.cpp -c 
g++ -g -std=c++11 -I ../Include  ../STC/*.cpp -c 
g++ -g -std=c++11 -I ../Include  ../Parser/Lexer.cpp ../Parser/Parser.c -c 
g++ -g *.o -o test
./test

