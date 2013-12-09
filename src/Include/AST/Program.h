#ifndef ST_8392618393_AST_PROGRAM
#define ST_8392618393_AST_PROGRAM
#include "AST.h"
namespace AST
{
	class StmtList;
	class Program : public AST
	{
	protected:
		Program(Location _loc);
		Program(const Program&);
	public:
		static Program* Create(StmtList* s1);
		void visit(Visitor* v);
	};
}
#endif
