#ifndef ST_8327192384_AST_CALLEXPR
#define ST_8327192384_AST_CALLEXPR
#include "Expr.h"
namespace AST
{
	class Oper;
	class CallExpr : public Expr
	{
	protected:
		CallExpr();
		CallExpr(const CallExpr&);
	public:
		static CallExpr* Create(Expr* s1, Oper* s2, Expr* s3, Oper* s4);
	};
}
#endif

