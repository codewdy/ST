#include "AST/Program.h"
#include "AST/Visitor.h"

namespace AST
{
	Program::Program(Location _loc) : AST(_loc) {}
	void Program::visit(Visitor* v)
	{
		return v->visitProgram(this);
	}
}
