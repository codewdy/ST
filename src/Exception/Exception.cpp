#include "Exception.h"
#include "ToolKit.h"
#include "BuiltinType/String.h"
#include "Runtime/VM.h"

namespace Exception {
    std::ostream *LogFile = &std::cout;
    void VMException::print(std::ostream& out) {
        for (auto item : trace)
            out << item.filename << ":" << item.lineno << std::endl;
        out << excpt["__str__"]().To<BuiltinType::String::Inner>() << std::endl;
    }
}
