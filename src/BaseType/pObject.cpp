#include "BaseType/pObject.h"
#include "Runtime/VM.h"
#include "BuiltinType/String.h"
#include "BuiltinType/Integer.h"
#include "BuiltinType/Double.h"
#include "BuiltinType/List.h"
#include "BuiltinType/Bool.h"

namespace BaseType {
    namespace pObjects {

        Object& pObjectBase::operator*() const {
            return *GetPtr();
        }
        Object* pObjectBase::operator->() const {
            return GetPtr();
        }
        pObjectBase::~pObjectBase() {
        }
#define ST_ARGS(...) std::vector<pObject>({__VA_ARGS__})
#define ST_CALC(OBJECT, NAME, ...) Runtime::VM::Calc((OBJECT)->getAttr(#NAME), ST_ARGS(__VA_ARGS__))
#define ST_DEF_OPER(OPER, FUNC) \
        pObject pObjectBase::operator OPER(const pObject& rhs) const {\
            return ST_CALC(GetPtr(), __##FUNC##__, rhs);\
        }
        ST_DEF_OPER(+, add)
        ST_DEF_OPER(-, minus)
        ST_DEF_OPER(*, mul)
        ST_DEF_OPER(/, div)
        ST_DEF_OPER(%, mod)
        ST_DEF_OPER(<, less_than)
        ST_DEF_OPER(>, greater_than)
        ST_DEF_OPER(<=, not_greater)
        ST_DEF_OPER(>=, not_less)
        ST_DEF_OPER(==, equal)
        ST_DEF_OPER(!=, not_equal)
        ST_DEF_OPER(&&, and)
        ST_DEF_OPER(||, or)
#define ST_DEF_SG_OPER(OPER, FUNC) \
        pObject pObjectBase::operator OPER() const {\
            return ST_CALC(GetPtr(), __##FUNC##__);\
        }
        ST_DEF_SG_OPER(!, not)
        ST_DEF_SG_OPER(-, neg)

        pObjectAttr pObjectBase::operator[](const std::string& attr) const {
            return {GetPtr(), attr};
        }
        pObjectAttr pObjectBase::operator[](std::string&& attr) const {
            return {GetPtr(), std::move(attr)};
        }

        pObject pObjectBase::Calc(std::vector<pObject>&& args) const {
            return Runtime::VM::Calc(GetPtr(), std::move(args));
        }
        pObject pObjectBase::Calc(const std::vector<pObject>& args) const {
            return Runtime::VM::Calc(GetPtr(), args);
        }

        void pObjectBase::SetAttr(const std::string& attr, const pObject& obj) const {
            GetPtr()->setAttr(attr, obj);
        }

        void pObjectBase::SetAttr(const std::string& attr, pObject&& obj) const {
            GetPtr()->setAttr(attr, std::move(obj));
        }

        //--------------pObject----------------------------------------------
        void pObject::Reduce() {
            //TODO
        }
        void pObject::Register() {
            //TODO
        }
        pObject::pObject(Object* _child) : child(_child) {
            Register();
        }
        pObject::pObject(const pObject& rhs) : child(rhs.child) {
            Register();
        }
        pObject::pObject(pObject&& rhs) : child(rhs.child) {
            rhs.child = nullptr;
        }
        pObject::pObject(std::initializer_list<std::pair<std::string, pObject>> lst) {
            child = new Object;
            Register();
            for (auto x : lst)
                child->setAttr(x.first, x.second);
        }
        pObject::pObject(std::nullptr_t arg) : pObject() {}
        pObject::pObject(bool arg) : pObject(BuiltinType::Bool::Create(arg)) {}
        pObject::pObject(int arg) : pObject(BuiltinType::Integer::Create(arg)) {}
        pObject::pObject(double arg) : pObject(BuiltinType::Double::Create(arg)) {}
        pObject::pObject(const std::string& arg) : pObject(BuiltinType::String::Create(arg)) {}
        pObject::pObject(std::string&& arg) : pObject(BuiltinType::String::Create(std::move(arg))) {}
        pObject::pObject(const char* arg) : pObject(BuiltinType::String::Create(arg)) {}
        pObject::pObject(const std::vector<pObject>& arg) : pObject(BuiltinType::List::Create(arg)) {}
        pObject::pObject(std::vector<pObject>&& arg) : pObject(BuiltinType::List::Create(std::move(arg))) {}

        pObject& pObject::operator=(const pObject &rhs) {
            Reduce();
            child = rhs.child;
            Register();
            return *this;
        }
        pObject& pObject::operator=(pObject &&rhs) {
            Reduce();
            child = rhs.child;
            rhs.child = nullptr;
            return *this;
        }
        pObject& pObject::operator=(Object* rhs) {
            Reduce();
            child = rhs;
            Register();
            return *this;
        }
        Object* pObject::GetPtr() const {
            return child;
        }
        pObject::~pObject() {
            Reduce();
            child = nullptr;
        }

        //---------------------pObjectExt---------------------------------------------------------------

        void pObjectExt::Reduce() {
            //TODO
        }
        void pObjectExt::Register() {
            //TODO
        }
        pObjectExt::pObjectExt(Object* _child, Object* _parent) : child(_child), parent(_parent) {
            Register();
        }
        pObjectExt::pObjectExt(const pObjectExt& rhs) : child(rhs.child), parent(rhs.parent) {
            Register();
        }
        pObjectExt::pObjectExt(pObjectExt&& rhs) : child(rhs.child), parent(rhs.parent) {
            rhs.child = nullptr;
        }
        pObjectExt& pObjectExt::operator=(const pObjectExt &rhs) {
            Reduce();
            child = rhs.child;
            parent = rhs.parent;
            Register();
            return *this;
        }
        pObjectExt& pObjectExt::operator=(pObjectExt &&rhs) {
            Reduce();
            child = rhs.child;
            parent = rhs.parent;
            rhs.child = nullptr;
            return *this;
        }
        pObjectExt& pObjectExt::operator=(Object* rhs) {
            Reduce();
            child = rhs;
            Register();
            return *this;
        }
        Object* pObjectExt::GetPtr() const {
            return child;
        }
        pObjectExt::~pObjectExt() {
            Reduce();
            child = nullptr;
        }

        pObjectExt::operator pObject() const {
            return GetPtr();
        }

        //---------------pObjectAttr--------------------------------------------------

        void pObjectAttr::Reduce() {
            //TODO
        }
        void pObjectAttr::Register() {
            //TODO
        }
        pObjectAttr::pObjectAttr(Object* _base, const std::string& _attr) : base(_base), attr(_attr) {
            Register();
        }
        pObjectAttr::pObjectAttr(Object* _base, std::string&& _attr) : base(_base), attr(std::move(_attr)) {
            Register();
        }
        pObjectAttr::pObjectAttr(const pObjectAttr& rhs) {
            base = rhs.base;
            attr = rhs.attr;
            Register();
        }
        pObjectAttr::pObjectAttr(pObjectAttr&& rhs) {
            base = rhs.base;
            attr = rhs.attr;
            rhs.base = nullptr;
        }
        const pObjectAttr& pObjectAttr::operator=(Object* rhs) const {
            base->setAttr(attr, rhs);
            return *this;
        }
        const pObjectAttr& pObjectAttr::operator=(const pObject& rhs) const {
            base->setAttr(attr, rhs.GetPtr());
            return *this;
        }
        const pObjectAttr& pObjectAttr::operator=(const pObjectBase& rhs) const {
            base->setAttr(attr, rhs.GetPtr());
            return *this;
        }
        const pObjectAttr& pObjectAttr::operator=(const pObjectAttr& rhs) const {
            base->setAttr(attr, rhs.GetPtr());
            return *this;
        }

        Object* pObjectAttr::GetPtr() const {
            Object* ret = base->getAttr(attr).GetPtr();
            return ret;
        }

        pObjectAttr::~pObjectAttr() {
            Reduce();
            base = nullptr;
        }

        pObjectAttr::operator pObject() const {
            return GetPtr();
        }
    }
}
