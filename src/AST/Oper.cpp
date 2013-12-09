#include "AST/Oper.h"
namespace AST
{
	Oper::Oper(Location _loc, const char* str) : AST(_loc), oper(GOPER(str)) {}
}
