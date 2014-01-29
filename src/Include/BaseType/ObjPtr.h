#ifndef ST_7872348237_BASETYPE_OBJPTR
#define ST_7872348237_BASETYPE_OBJPTR
#include <map>
#include <set>
#include <list>

namespace BaseType {
    class Object;
    /**A Pointer to Object with GC.*/
    class ObjPtr {
        /**Map to the Relations about parent and child.*/
        static std::map<Object*, std::map<Object*, std::size_t>> Map;
        /**Set about handled Object.*/
        static std::set<Object*> HandledPtr;
        /**A Inner struct about Map Insert/Delete.*/
        struct Operator {
            Object *parent, *child;
            int delta;
            Operator(Object *_parent, Object* _child, int _delta) : parent(_parent), child(_child), delta(_delta) {}
        };
        /**To Save Map Changes When Freze the Map.*/
        static std::list<Operator> Opers;
        /**the Pointer point to.*/
        Object *child;
        /**the Pointer's Owner.*/
        Object *parent;
        /**Reduce the referrence.*/
        void Reduce();
        /**Regist the Pointer.*/
        void Register();
        /**Change the Child to a new Child, But Not Change the parent.*/
        void ChangeChild(Object *_child);
    public:
        ObjPtr(Object* _child = 0, Object* _parent = 0);
        ObjPtr(const ObjPtr& rhs);
        ObjPtr& operator=(const ObjPtr& rhs);
        ObjPtr& operator=(Object* rhs);
        operator Object*();
        Object& operator*();
        Object* operator->();
        ~ObjPtr();
        /**A Single GC Step.*/
        static void GCStep();
        /**Multi-Step to GC.*/
        static void GC();
        /**GC All to Make Map disfrozen. \warning that function may product a time bottlenect.*/
        static void FullGC();
    };
}
#endif
