#ifndef ST_7394856291_AST_AST
#define ST_7394856291_AST_AST
#include <memory>
#include <string>
#include <vector>

namespace AST
{
	extern std::vector<std::string> source;
	extern std::string* currentSource;
	class Visitor;
	struct Location
	{
		std::string* str;
		std::size_t lineno;
		Location(std::string* _str = 0, std::size_t _lineno = 0) : str(_str), lineno(_lineno) {}
	};
	class AST;
	typedef AST* Node;
	class AST
	{
	public:
		AST(Location _loc);
		//virtual void visit(Visitor* v) = 0; 
	};
}
#endif

