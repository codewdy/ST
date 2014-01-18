#include "AST/AST.h"
#include "Exception/NotImplement.h"
namespace AST {
    void AST::visit(Visitor* v) {
        Raise(NotImplement);
    }
}
