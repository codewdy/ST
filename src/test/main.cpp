#include "ASTPrinter.h"
#include "STCPrinter.h"
#include "STC/Generator.h"
#include "Parser.h"

int main() {
    AST::Program* ast = CreateAST("test.st");
    ASTPrinter astprinter(std::cout);
    astprinter.visitProgram(ast);
    STC::Generator gen;
    STC::STC* stc = gen.Gen(ast);
    STCPrinter(stc);
}
