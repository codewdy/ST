#ifndef ST_7872348237_BASETYPE_POBJECT
#define ST_7872348237_BASETYPE_POBJECT

#include <string>
#include <vector>

namespace BaseType {
    class Object;
    namespace pObjects {
        class pObjectAttr;
        class pObject;
        class pObjectBase {
        protected:
            /**Reduce the referrence.*/
            virtual void Reduce() = 0;
            /**Regist the Pointer.*/
            virtual void Register() = 0;
        public:
            Object& operator*() const;
            Object* operator->() const;
            virtual ~pObjectBase();


            explicit operator bool() const = delete;
            pObject operator+(const pObject& rhs) const;
            pObject operator-(const pObject& rhs) const;
            pObject operator*(const pObject& rhs) const;
            pObject operator/(const pObject& rhs) const;
            pObject operator%(const pObject& rhs) const;
            pObject operator<(const pObject& rhs) const;
            pObject operator>(const pObject& rhs) const;
            pObject operator<=(const pObject& rhs) const;
            pObject operator>=(const pObject& rhs) const;
            pObject operator==(const pObject& rhs) const;
            pObject operator!=(const pObject& rhs) const;
            pObject operator&&(const pObject& rhs) const;
            pObject operator||(const pObject& rhs) const;
            pObject operator!() const;
            pObject operator-() const;
            pObjectAttr operator[](const std::string& attr) const;
            pObjectAttr operator[](std::string&& attr) const;
            pObject Calc(std::vector<pObject>&& args) const;
            pObject Calc(const std::vector<pObject>& args) const;
            template <typename... Arg>
            pObject operator()(Arg... args) const;
            void SetAttr(const std::string& attr, const pObject& obj) const;
            void SetAttr(const std::string& attr, pObject&& obj) const;
            virtual Object* GetPtr() const = 0;
            bool ref_equal(Object* rhs) const {
                return GetPtr() == rhs;
            }
            bool ref_equal(const pObjectBase& rhs) const {
                return GetPtr() == rhs.GetPtr();
            }
            bool ref_not_equal(Object* rhs) const {
                return GetPtr() != rhs;
            }
            bool ref_not_equal(const pObjectBase& rhs) const {
                return GetPtr() != rhs.GetPtr();
            }

            //It is defined in ToolKit.h
            template <class T>
            T& To() const;
        };
        /**A Pointer to Object on GC Map's Top (like an pObjectExt with 0 parent but more quicker).*/
        class pObject : public pObjectBase {
        protected:
            /**the Pointer point to.*/
            Object* child;
            /**Reduce the referrence.*/
            virtual void Reduce();
            /**Regist the Pointer.*/
            virtual void Register();
        public:
            pObject(Object* _child = nullptr);
            pObject(const pObject& rhs);
            pObject(pObject&& rhs);
            pObject& operator=(const pObject& rhs);
            pObject& operator=(pObject&& rhs);
            pObject& operator=(Object* rhs);
            virtual Object* GetPtr() const;
            virtual ~pObject();
        };
        /**A Pointer to Object on GC Map.*/
        class pObjectExt : public pObjectBase {
        protected:
            /**the Pointer point to.*/
            Object* child;
            /**the Pointer's Owner.*/
            Object *parent;
            /**Reduce the referrence.*/
            virtual void Reduce();
            /**Regist the Pointer.*/
            virtual void Register();
        public:
            pObjectExt(Object* _child = nullptr, Object* _parent = nullptr);
            pObjectExt(const pObject& _child, const pObject& _parent) : pObjectExt(_child.GetPtr(), _parent.GetPtr()) {}
            pObjectExt(const pObjectExt& rhs);
            pObjectExt(pObjectExt&& rhs);
            pObjectExt& operator=(const pObjectExt& rhs);
            pObjectExt& operator=(pObjectExt&& rhs);
            pObjectExt& operator=(Object* rhs);
            virtual Object* GetPtr() const;
            virtual ~pObjectExt();
            operator pObject() const;
        };
        class pObjectAttr : public pObjectBase {
        protected:
            /**the parent of the Attr.*/
            Object* base;
            /**the attribute for child.*/
            std::string attr;
            /**Reduce the referrence.*/
            virtual void Reduce();
            /**Regist the Pointer.*/
            virtual void Register();
        public:
            pObjectAttr(Object* _base, const std::string& _attr);
            pObjectAttr(Object* _base, std::string&& _attr);
            pObjectAttr(const pObjectAttr& rhs);
            pObjectAttr(pObjectAttr&& rhs);
            const pObjectAttr& operator=(Object* rhs) const;
            const pObjectAttr& operator=(const pObjectBase& rhs) const;
            const pObjectAttr& operator=(const pObjectAttr& rhs) const;
            virtual Object* GetPtr() const;
            virtual ~pObjectAttr();
            operator pObject() const;
        };

        template <typename... Arg>
        inline pObject pObjectBase::operator()(Arg... args) const {
            return Calc({args...});
        }
    }
}

using BaseType::pObjects::pObject;
using BaseType::pObjects::pObjectExt;

#endif
