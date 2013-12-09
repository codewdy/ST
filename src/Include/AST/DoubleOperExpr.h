#ifndef ST_1021907482_AST_DOUBLEOPEREXPR
#define ST_1021907482_AST_DOUBLEOPEREXPR
#include "Expr.h"
namespace AST
{
	class Oper;
	class DoubleOperExpr : public Expr
	{
	protected:
		DoubleOperExpr();
		DoubleOperExpr(const DoubleOperExpr&);
	public:
		static DoubleOperExpr* Create(Oper* s1, Expr* s2, Oper* s3);
	};
}
#endif

