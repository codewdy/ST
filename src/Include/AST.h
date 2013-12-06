#ifndef ST_AST
#define ST_AST
#include <memory>

class AST
{
public:
	typedef std::shared_ptr<AST> Node;
	struct Location
	{
	  int first_line;  
	  int first_column;  
	  int last_line;  
	  int last_column;  
	} loc;
	class Visitor;
	virtual void visit(Visitor* v) = 0; 
};

class AST::Visitor
{
};
#endif
