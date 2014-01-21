#ifndef ST_3272840193_AST_LVALUELIST
#define ST_3272840193_AST_LVALUELIST
#include "AST.h"
#include <vector>
namespace AST
{
    class LValue;
    class LValueList : public AST
    {
    protected:
        LValueList();
        LValueList(const LValueList&);
    public:
        std::vector<LValue*> exprs;
        static LValueList* Create();
        static LValueList* Create(LValue* right);
        static LValueList* Create(LValueList* left, LValue* right);
        static void FillVector(LValueList* src, std::vector<LValue*>& dst);
    };
}
#endif
