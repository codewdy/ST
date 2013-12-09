#ifndef ST_3749102485_AST_OPER
#define ST_3749102485_AST_OPER
#include "AST.h"
#define GOPER(str) (str[1] * 256 + str[0])
namespace AST
{
	class Oper : public AST
	{
	public:
		int oper;
		Oper(Location _loc, const char* str);
	};
}
#endif

