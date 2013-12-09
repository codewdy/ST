#ifndef ST_7482647236_AST_DOUBLE
#define ST_7482647236_AST_DOUBLE
#include "Expr.h"
namespace AST
{
	class Double : public Expr
	{
	public:
		Double(Location _loc, const char* str);
	};
}
#endif

