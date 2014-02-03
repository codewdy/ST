#include "BaseType/ObjPtr.h"
#include <cmath>

namespace BaseType {
    //Define the static Varibles
    std::map<Object*, std::map<Object*, std::size_t>> ObjPtr::Map;
    std::set<Object*> ObjPtr::HandledPtr;
    std::list<ObjPtr::Operator> ObjPtr::Opers;

    void ObjPtr::Reduce() {
        if (child)
            Opers.push_back(Operator(parent, child, -1));
    }

    void ObjPtr::Register() {
        if (child)
            Opers.push_back(Operator(parent, child, 1));
    }

    void ObjPtr::ChangeChild(Object* _child) {
        if (child)
            Opers.push_back(Operator(parent, child, -1));
        child = _child;
        if (child)
            Opers.push_back(Operator(parent, child, 1));
    }

    ObjPtr::ObjPtr(Object* _child, Object* _parent) : child(_child), parent(_parent) {
        Register();
    }

    ObjPtr::ObjPtr(const ObjPtr& obj) : child(obj.child), parent(obj.parent) {
        Register();
    }

    ObjPtr& ObjPtr::operator=(const ObjPtr& rhs) {
        ChangeChild(rhs.child);
        return *this;
    }

    ObjPtr& ObjPtr::operator=(Object* rhs) {
        ChangeChild(rhs);
        return *this;
    }

    ObjPtr::operator class BaseType::Object *() {
        return child;
    }

    Object& ObjPtr::operator*() {
        return *child;
    }

    Object* ObjPtr::operator->() {
        return child;
    }

    ObjPtr::~ObjPtr() {
        Reduce();
        child = 0;
    }

    void ObjPtr::GC() {
        int num = int(sqrt(Opers.size())) + 1;
        for (int i = 0; i < num; i++)
            GCStep();
    }

    void ObjPtr::FullGC() {
        while (!Opers.empty())
            GCStep();
    }

    //Some Static Varible For GCStep
    static enum GCMode {
        PushOp,
        Init,
        BFS,
        Clear,
    } gcMode = PushOp;
    static std::set<Object*> bfsFlag;
    static std::list<Object*> bfsList;
    static std::set<Object*>::iterator SetIter1, SetIter2;
    static std::map<Object*, std::size_t>::iterator MapIter1, MapIter2;
    static std::map<Object*, std::map<Object*, std::size_t>>::iterator MapMapIter;
    static int CD = 0;

    void ObjPtr::GCStep() {
        switch (gcMode) {
        case PushOp:
            if (!Opers.empty()) {
                auto tmp = Opers.begin();
                if (tmp->delta > 0)
                    HandledPtr.insert(tmp->child);
                if ((Map[tmp->parent][tmp->child] += tmp->delta) == 0)
                    Map[tmp->parent].erase(tmp->child);
                Opers.pop_front();
            }
            if (++CD > int(sqrt(HandledPtr.size())) + 30) {
                CD = 0;
                gcMode = Init;
                SetIter1 = HandledPtr.begin();
                SetIter2 = bfsFlag.end();
            }
            break;
        case Init:
            SetIter2 = bfsFlag.insert(SetIter2, *SetIter1);
            if (++SetIter1 == HandledPtr.end()) {
                MapMapIter = Map.find(0);
                MapIter1 = MapMapIter->second.begin();
                MapIter2 = MapMapIter->second.end();
                gcMode = BFS;
            }
            break;
        case BFS:
            if (MapIter1 != MapIter2) {
                if ((SetIter1 = bfsFlag.find(MapIter1->first)) !=bfsFlag.end()) {
                    bfsFlag.erase(SetIter1);
                    bfsList.push_back(MapIter1->first);
                }
                MapIter1++;
            } else if (!bfsList.empty()) {
                MapMapIter = Map.find(*bfsList.begin());
                if (MapMapIter != Map.end()) {
                    MapIter1 = MapMapIter->second.begin();
                    MapIter2 = MapMapIter->second.end();
                    bfsList.pop_front();
                }
            } else {
                MapMapIter = Map.end();
                SetIter1 = bfsFlag.begin();
                gcMode = Clear;
            }
            break;
        case Clear:
            if (MapIter1 != MapIter2) {
                auto tmp = MapIter1++;
                MapMapIter->second.erase(tmp);
            } else{
                if (MapMapIter != Map.end())
                    Map.erase(MapMapIter);
                if (SetIter1 != bfsFlag.end()) {
                    MapMapIter = Map.find(*SetIter1);
                    if (MapMapIter != Map.end()) {
                        MapIter1 = MapMapIter->second.begin();
                        MapIter2 = MapMapIter->second.end();
                    }
                    auto tmp = SetIter1++;
                    bfsFlag.erase(tmp);
                } else {
                    CD = 0;
                    gcMode = PushOp;
                }
            } 
            break;
        }
    }
}
