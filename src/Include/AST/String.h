#ifndef ST_2837461829_AST_STRING
#define ST_2837461829_AST_STRING
#include "Expr.h"
#include <string>
namespace AST
{
	class String : public Expr
	{
	public:
		std::string str;
		String(Location _loc, std::string _str);
		void visit(Visitor* v);
	};
}
#endif

