#ifndef ST_2873292179_AST_INTEGER
#define ST_2873292179_AST_INTEGER
#include "Expr.h"
namespace AST
{
	class Integer : public Expr
	{
	public:
		Integer(Location _loc, const char* str);
	};
}
#endif

