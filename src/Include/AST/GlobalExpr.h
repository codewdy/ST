#ifndef ST_82371923842_AST_GLOBALEXPR
#define ST_82371923842_AST_GLOBALEXPR
#include "Expr.h"
namespace AST
{
	class GlobalExpr : public Expr
	{
	protected:
		GlobalExpr();
		GlobalExpr(const GlobalExpr&);
	public:
		static GlobalExpr* Create();
	};
}
#endif

