#ifndef ST_3749102485_AST_OPER
#define ST_3749102485_AST_OPER
#include "AST.h"
namespace AST
{
	class Oper : public AST
	{
	public:
		Oper(Location _loc, const char* str);
	};
}
#endif

