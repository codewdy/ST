#ifndef ST_3291283292_AST_SINGLEOPEREXPR
#define ST_3291283292_AST_SINGLEOPEREXPR
#include "Expr.h"
namespace AST
{
	class Oper;
	class SingleOperExpr : public Expr
	{
	protected:
		SingleOperExpr();
		SingleOperExpr(const SingleOperExpr&);
	public:
		static SingleOperExpr* Create(Oper* s1, Expr* s2);
	};
}
#endif
