#ifndef ST_2837461829_AST_STRING
#define ST_2837461829_AST_STRING
#include "Expr.h"
#include <string>
namespace AST
{
	class String : public Expr
	{
	public:
		String(Location _loc, std::string str);
	};
}
#endif

