#include "STC/ALL.h"
#include <unordered_map>
#include <unordered_set>

namespace STC {
    struct SerializeHelper {
        std::vector<STC*> codes;
        std::vector<int> gotos;
        std::unordered_map<STC*, std::size_t> index;
        void Append(STC* code) {
            index[code] = codes.size();
            codes.push_back(code);
        }

        void EncodeCore(STC* lst) {
            for (; lst; lst = lst->next) {
                Append(lst);
                if (lst->arg == STC::BlockArg)
                    EncodeCore(lst->code);
            }
            Append(0);
        }
        void Encode(STC* lst) {
            EncodeCore(lst);
            for (auto code : codes)
                if (code && code->arg == STC::GotoArg)
                    gotos.push_back(index[code->code]);
        }

        STC* DecodeCore(int& i, int& j) {
            i++;
            STC* ret = codes[i];
            for (; i < codes.size(); i++) {
                STC* cur = codes[i];
                if (cur == 0)
                    return ret;
                else
                    switch (cur->arg) {
                        case STC::BlockArg:
                            cur->code = DecodeCore(i, j);
                            cur->next = codes[i + 1];
                            break;
                        case STC::GotoArg:
                            if (j >= gotos.size() || gotos[j] >= codes.size()) {
                                //TODO: Throw A Exception.
                            }
                            cur->code = codes[gotos[j++]];
                            cur->next = codes[i + 1];
                            break;
                        default:
                            cur->next = codes[i + 1];
                            break;
                    }
            }
            throw "Inner Error!";
        }

        STC* Decode() {
            int i = -1, j = 0;
            return DecodeCore(i, j);
        }
    };

    static void WriteInt(std::ostream& out, unsigned int x) {
        unsigned int x1 = x >> 0 & 0xFF;
        unsigned int x2 = x >> 8 & 0xFF;
        unsigned int x3 = x >> 16 & 0xFF;
        unsigned int x4 = x >> 24 & 0xFF;
        out.put(x1);
        out.put(x2);
        out.put(x3);
        out.put(x4);
    }

    static unsigned int ReadInt(std::istream& in) {
        unsigned int x1 = in.get() & 0xFF;
        unsigned int x2 = in.get() & 0xFF;
        unsigned int x3 = in.get() & 0xFF;
        unsigned int x4 = in.get() & 0xFF;
        unsigned int xx = (x1 + 256 * (x2 + 256 * (x3 + 256 * x4)));
        return xx;
    }
    
    static void WriteString(std::ostream& out, const std::string& str) {
        WriteInt(out, str.size());
        out.write(str.c_str(), str.size());
    }

    static std::string ReadString(std::istream& in) {
        int size = ReadInt(in);
        char* re = new char[size + 1];
        in.read(re, size);
        std::string ret(re, re + size);
        delete re;
        return ret;
    }

    static const char EOB = '\255';
    void Writer(std::ostream& out, STC* lst) {
        SerializeHelper helper;
        helper.Encode(lst);
        for (auto code : helper.codes) {
            if (code == 0) {
                out.put(EOB);
            } else {
                out.put((char)code->type);
                switch (code->arg) {
                    case STC::NoneArg:
                    case STC::BlockArg:
                    case STC::GotoArg:
                        break;
                    case STC::IntArg:
                        WriteInt(out, code->num);
                        break;
                    case STC::StringArg:
                        WriteString(out, code->str);
                        break;
                }
            }
        }
        WriteInt(out, helper.gotos.size());
        for (auto item : helper.gotos)
            WriteInt(out, item);
    }
    STC* Reader(std::istream& in) {
        int depth = 0;
        SerializeHelper helper;
        bool flag = true;
        while (in && flag) {
            char type = in.get();
            if (type == EOB) {
                helper.Append(0);
                if (depth-- == 0)
                    flag = false;
            } else
                switch (STC::ArgMap[type]) {
                    case STC::NoneArg:
                        helper.Append(new STC((STC::Type)type));
                        break;
                    case STC::StringArg:
                        helper.Append(new STC((STC::Type)type, ReadString(in)));
                        break;
                    case STC::IntArg:
                        helper.Append(new STC((STC::Type)type, ReadInt(in)));
                        break;
                    case STC::GotoArg:
                        helper.Append(new STC((STC::Type)type, (STC*)0));
                        break;
                    case STC::BlockArg:
                        helper.Append(new STC((STC::Type)type, (STC*)0));
                        depth++;
                        break;
                }
        }
        int sz = ReadInt(in);
        helper.gotos.resize(sz);
        for (int i = 0; i < sz && in; i++)
            helper.gotos[i] = ReadInt(in);
        if (!in) {
            //TODO: Add An Exception.
        }
        return helper.Decode();
    }
}
