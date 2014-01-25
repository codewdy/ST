#include "ASTPrinter.h"
#include <iostream>

#define DefPrintFunc(CLASS, MSG) \
void ASTPrinter::visit##CLASS(AST::CLASS* that) {\
    fout << prefix << MSG << std::endl;\
    std::string save = prefix;\
    prefix += "|   ";\
    Visitor::visit##CLASS(that);\
    prefix = save;\
}

#define SimpleDefPrintFunc(CLASS) DefPrintFunc(CLASS, #CLASS << ":")

SimpleDefPrintFunc(Program)
SimpleDefPrintFunc(SimpleStmt)
SimpleDefPrintFunc(ForStmt)
SimpleDefPrintFunc(WhileStmt)
SimpleDefPrintFunc(IfStmt)
SimpleDefPrintFunc(StmtBlock)
SimpleDefPrintFunc(BreakStmt)
SimpleDefPrintFunc(ReturnStmt)
SimpleDefPrintFunc(ListExpr)
SimpleDefPrintFunc(CallExpr)
SimpleDefPrintFunc(FuncDef)
SimpleDefPrintFunc(StateDef)
SimpleDefPrintFunc(GlobalExpr)
SimpleDefPrintFunc(LocaleExpr)
DefPrintFunc(DoubleOperExpr, "DoubleOperStmt[" << that->oper << "]:")
DefPrintFunc(SingleOperExpr, "SimpleOperStmt[" << that->oper << "]:")
DefPrintFunc(VarLValue, "VarLValue[" << that->attr << "]:")
DefPrintFunc(Double, "Double[" << that->str << "]:")
DefPrintFunc(Integer, "Integer[" << that->str << "]:")
DefPrintFunc(String, "String[" << that->str << "]:")
