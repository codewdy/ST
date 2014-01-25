#include "ASTPrinter.h"
#include "STCPrinter.h"
#include "STC/ALL.h"
#include "Parser.h"
#include <iostream>
#include <fstream>

int main() {
    AST::Program* ast = CreateAST("test.st");
    ASTPrinter astprinter(std::cout);
    astprinter.visitProgram(ast);
    STC::Generator gen;
    STC::STC* stc = gen.Gen(ast);
    STCPrinter(stc);
    std::ofstream of("test.stc");
    STC::Writer(of, stc);
    of.close();
    std::ifstream iif("test.stc");
    STC::STC* stc2 = STC::Reader(iif);
    STCPrinter(stc2);
}
