#ifndef ST_7681943681_STC_SERIALIZE
#define ST_7681943681_STC_SERIALIZE
#include "STC.h"
#include <iostream>
namespace STC {
    void Writer(std::ostream& out, STCList codes);
    STCList Reader(std::istream& out);
}
#endif
