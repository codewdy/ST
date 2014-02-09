#include "BaseType/pObject.h"
#include "Runtime/VM.h"

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
#define ARGS(...) std::vector<pObject>({__VA_ARGS__})
#define CALC(OBJECT, NAME, ...) Runtime::VM::Calc((OBJECT)->getAttr(#NAME), ARGS(__VA_ARGS__))
#define DEF_OPER(OPER, FUNC) \
        pObject pObjectBase::operator OPER(const pObject& rhs) const {\
            return CALC(GetPtr(), __##FUNC##__, rhs);\
        }
        DEF_OPER(+, add)
        DEF_OPER(-, minus)
        DEF_OPER(*, mul)
        DEF_OPER(/, div)
        DEF_OPER(%, mod)
        DEF_OPER(<, less_than)
        DEF_OPER(>, greater_than)
        DEF_OPER(<=, not_greater)
        DEF_OPER(>=, not_less)
        DEF_OPER(==, equal)
        DEF_OPER(!=, not_equal)
        DEF_OPER(&&, and)
        DEF_OPER(||, or)
#define DEF_SG_OPER(OPER, FUNC) \
        pObject pObjectBase::operator OPER() const {\
            return CALC(GetPtr(), __##FUNC##__);\
        }
        DEF_SG_OPER(!, not)
        DEF_SG_OPER(-, neg)

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
