#include "ASTPrinter.h"
#include "STCPrinter.h"
#include "STC/ALL.h"
#include "Parser.h"
#include "BaseType/Init.h"
#include "BuiltinType/Init.h"
#include "Runtime/VM.h"
#include <iostream>
#include <fstream>

int main() {
    try {
    AST::Program* ast = Parser::CreateAST("test.st");
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
    std::cout << std::endl;
    STCPrinter(stc2);
    BaseType::InitState();
    BuiltinType::InitState();
    Runtime::VM vm(stc2);
    vm.Run();
    } catch (const char* x) {
        std::cerr << x << std::endl;
    }
}
