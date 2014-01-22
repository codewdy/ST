#include "ASTPrinter.h"
#include "Parser.h"

int main() {
    AST::Program* ast = CreateAST("test.st");
    ASTPrinter printer(std::cout);
    printer.visitProgram(ast);
}
