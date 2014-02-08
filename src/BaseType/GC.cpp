#include "BaseType/GC.h"

namespace BaseType {
    namespace GC {
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
        pObjectExt::operator Object*() const {
            return child;
        }
        Object& pObjectExt::operator*() const {
            return *child;
        }
        Object* pObjectExt::operator->() const {
            return child;
        }
        pObjectExt::~pObjectExt() {
            Reduce();
        }

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
        pObject::operator Object*() const {
            return child;
        }
        Object& pObject::operator*() const {
            return *child;
        }
        Object* pObject::operator->() const {
            return child;
        }
        pObject::~pObject() {
            Reduce();
        }
    }
}
