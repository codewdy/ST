#ifndef ST_8271892302_AST_VARLVALUE
#define ST_8271892302_AST_VARLVALUE
#include "LValue.h"
namespace AST
{
	class Identifier;
	class Expr;
	class Oper;
	class VarLValue : public LValue
	{
	protected:
		VarLValue();
		VarLValue(const VarLValue&);
	public:
		static VarLValue* Create(Identifier* s1);
		static VarLValue* Create(Expr* s1, Oper* s2, Identifier* s3);
	};
}
#endif

