#ifndef ST_7482647236_AST_DOUBLE
#define ST_7482647236_AST_DOUBLE
#include "AST.h"
namespace AST
{
	class Double : public AST
	{
	public:
		Double(Location _loc, const char* str);
	};
}
#endif

