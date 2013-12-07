#ifndef FRONTEND_PARSERDEF
#define FRONTEND_PARSERDEF
#include "AST.h"
#define YYSTYPE AST::Node
#define YYLTYPE AST::Location
#endif
