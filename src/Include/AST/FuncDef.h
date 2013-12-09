#ifndef ST_8291827482_AST_FUNCDEF
#define ST_8291827482_AST_FUNCDEF
#include "Expr.h"
namespace AST
{
	class Keyword;
	class IDs;
	class Oper;
	class StmtBlock;
	class FuncDef : public Expr
	{
	protected:
		FuncDef();
		FuncDef(const FuncDef&);
	public:
		static FuncDef* Create(Keyword* s1, IDs* s2, Oper* s3, IDs* s4, Oper* s5, StmtBlock* s6);
	};
}
#endif
