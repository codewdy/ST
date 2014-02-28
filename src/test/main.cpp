#include "ASTPrinter.h"
#include "STCPrinter.h"
#include "STC/ALL.h"
#include "Parser.h"
#include "BaseType/Init.h"
#include "BuiltinType/Init.h"
#include "Runtime/VM.h"
#include "Exception.h"
#include <iostream>
#include <fstream>

int main(int argc, char* argv[]) {
    try {
    AST::Program* ast = Parser::CreateAST(argv[1]);
    ASTPrinter astprinter(*(Exception::LogFile));
    astprinter.visitProgram(ast);
    STC::Generator gen;
    STC::STC* stc = gen.Gen(ast);
    STCPrinter(stc);
    std::ofstream of("result.stc");
    STC::Writer(of, stc);
    of.close();
    std::ifstream iif("result.stc");
    STC::STC* stc2 = STC::Reader(iif);
    *(Exception::LogFile) << std::endl;
    STCPrinter(stc2);
    BaseType::InitState();
    BuiltinType::InitState();
    Runtime::VM vm(stc2);
    vm.Run();
    } catch (const char* x) {
        std::cerr << x << std::endl;
    } catch (Exception::SyntaxException e) {
        std::cerr << e.filename << std::endl;
        std::cerr << e.lineno << std::endl;
    } catch (Exception::VMException e) {
        e.print(*(Exception::LogFile));
    }
}
