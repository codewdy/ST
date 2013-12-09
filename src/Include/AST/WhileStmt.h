#ifndef ST_0901238293_AST_WHILESTMT
#define ST_0901238293_AST_WHILESTMT
#include "Stmt.h"
namespace AST
{
	class Keyword;
	class Oper;
	class Expr;
	class WhileStmt : public Stmt
	{
	protected:
		WhileStmt();
		WhileStmt(const WhileStmt&);
	public:
		static WhileStmt* Create(Keyword* s1, Oper* s2, Expr* s3, Oper* s4, Stmt* s5);
	};
}
#endif

