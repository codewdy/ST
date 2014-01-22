#ifndef FRONTEND_PARSERDEF
#define FRONTEND_PARSERDEF
#include "AST/ALL.h"
struct Lex {
    std::string str;
    int type;
    AST::Location loc;
    Lex(std::string _str, int _type, AST::Location _loc) : str(_str), type(_type), loc(_loc) {}
};
#endif

