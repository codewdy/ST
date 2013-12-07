#ifndef ST_2873292179_AST_INTEGER
#define ST_2873292179_AST_INTEGER
#include "AST.h"
namespace AST
{
	class Integer : public AST
	{
	public:
		Integer(Location _loc, const char* str);
	};
}
#endif

