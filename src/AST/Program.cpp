#include "AST/Program.h"
#include "AST/Visitor.h"

namespace AST {
    void Program::visit(Visitor* v) {
        return v->visitProgram(this);
    }
}
