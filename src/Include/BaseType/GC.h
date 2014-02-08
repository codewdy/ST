#ifndef ST_7872348237_BASETYPE_GC
#define ST_7872348237_BASETYPE_GC

namespace BaseType {
    class Object;
    namespace GC {
        /**A Pointer to Object on GC Map.*/
        class pObjectExt {
            /**the Pointer point to.*/
            Object *child;
            /**the Pointer's Owner.*/
            Object *parent;
            /**Reduce the referrence.*/
            void Reduce();
            /**Regist the Pointer.*/
            void Register();
        public:
            pObjectExt(Object* _child = nullptr, Object* _parent = nullptr);
            pObjectExt(const pObjectExt& rhs);
            pObjectExt(pObjectExt&& rhs);
            pObjectExt& operator=(const pObjectExt& rhs);
            pObjectExt& operator=(pObjectExt&& rhs);
            pObjectExt& operator=(Object* rhs);
            operator Object*() const;
            Object& operator*() const;
            Object* operator->() const;
            ~pObjectExt();
        };
        /**A Pointer to Object on GC Map's Top (like an pObjectExt with 0 parent but more quicker).*/
        class pObject {
            /**the Pointer point to.*/
            Object* child;
            /**Reduce the referrence.*/
            void Reduce();
            /**Regist the Pointer.*/
            void Register();
        public:
            pObject(Object* _child = nullptr);
            pObject(const pObject& rhs);
            pObject(pObject&& rhs);
            pObject& operator=(const pObject& rhs);
            pObject& operator=(pObject&& rhs);
            pObject& operator=(Object* rhs);
            operator Object*() const;
            Object& operator*() const;
            Object* operator->() const;
            ~pObject();
        };
    }
}

using BaseType::GC::pObject;
using BaseType::GC::pObjectExt;

#endif
