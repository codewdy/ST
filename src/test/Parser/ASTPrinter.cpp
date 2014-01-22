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

DefPrintFunc(Program, "Program:")
DefPrintFunc(SimpleStmt, "SimpleStmt:")
DefPrintFunc(DoubleOperExpr, "DoubleOperStmt[" << that->oper << "]:")
DefPrintFunc(VarLValue, "VarLValue[" << that->attr << "]:")
DefPrintFunc(Double, "Double[" << that->str << "]:")
DefPrintFunc(Integer, "Integer[" << that->str << "]:")
DefPrintFunc(String, "String[" << that->str << "]:")
