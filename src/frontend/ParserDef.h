#ifndef FRONTEND_PARSERDEF
#define FRONTEND_PARSERDEF
#include "AST/ALL.h"
struct Lex {
    std::string str;
    int type;
    AST::Location loc;
};
#endif

