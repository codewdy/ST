#ifndef ST_2738193827_AST_STMTLIST
#define ST_2738193827_AST_STMTLIST
#include "AST.h"
namespace AST
{
	class Stmt;
	class StmtList : public AST
	{
	protected:
		StmtList();
		StmtList(const StmtList&);
	public:
		static StmtList* Create();
		static StmtList* Create(StmtList* s1, Stmt* s2);
	};
}
#endif
