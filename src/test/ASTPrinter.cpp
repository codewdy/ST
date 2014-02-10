#include "ASTPrinter.h"
#include <iostream>

#define ST_DEF_PRINT_FUNC(CLASS, MSG) \
void ASTPrinter::visit##CLASS(AST::CLASS* that) {\
    fout << prefix << MSG << std::endl;\
    std::string save = prefix;\
    prefix += "|   ";\
    Visitor::visit##CLASS(that);\
    prefix = save;\
}

#define ST_SIMPLE_DEF_PRINT_FUNC(CLASS) ST_DEF_PRINT_FUNC(CLASS, #CLASS << ":")

ST_SIMPLE_DEF_PRINT_FUNC(Program)
ST_SIMPLE_DEF_PRINT_FUNC(SimpleStmt)
ST_SIMPLE_DEF_PRINT_FUNC(ForStmt)
ST_SIMPLE_DEF_PRINT_FUNC(WhileStmt)
ST_SIMPLE_DEF_PRINT_FUNC(IfStmt)
ST_SIMPLE_DEF_PRINT_FUNC(StmtBlock)
ST_SIMPLE_DEF_PRINT_FUNC(BreakStmt)
ST_SIMPLE_DEF_PRINT_FUNC(ReturnStmt)
ST_SIMPLE_DEF_PRINT_FUNC(ListExpr)
ST_SIMPLE_DEF_PRINT_FUNC(CallExpr)
ST_SIMPLE_DEF_PRINT_FUNC(FuncDef)
ST_SIMPLE_DEF_PRINT_FUNC(StateDef)
ST_SIMPLE_DEF_PRINT_FUNC(GlobalExpr)
ST_SIMPLE_DEF_PRINT_FUNC(LocaleExpr)
ST_SIMPLE_DEF_PRINT_FUNC(NullExpr)
ST_SIMPLE_DEF_PRINT_FUNC(ArrayAtLValue)
ST_DEF_PRINT_FUNC(DoubleOperExpr, "DoubleOperStmt[" << that->oper << "]:")
ST_DEF_PRINT_FUNC(SingleOperExpr, "SimpleOperStmt[" << that->oper << "]:")
ST_DEF_PRINT_FUNC(VarLValue, "VarLValue[" << that->attr << "]:")
ST_DEF_PRINT_FUNC(Double, "Double[" << that->str << "]:")
ST_DEF_PRINT_FUNC(Integer, "Integer[" << that->str << "]:")
ST_DEF_PRINT_FUNC(String, "String[" << that->str << "]:")
