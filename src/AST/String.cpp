#include "AST/String.h"
#include "AST/Visitor.h"

namespace AST
{
	String::String(Location _loc, std::string _str) : Expr(_loc), str(_str) {}
	void String::visit(Visitor* v)
	{
		v->visitString(this);
	}
}

