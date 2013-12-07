#ifndef ST_AST
#define ST_AST
#include <memory>

namespace AST
{
	class Visitor;
	struct Location
	{
	  int line;  
	  int column;  
	};
	class AST;
	typedef std::shared_ptr<AST> Node;
	class AST
	{
	public:
		Location loc;
		virtual void visit(Visitor* v) = 0; 
	};
}
#endif
