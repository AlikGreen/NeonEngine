#include "file.h"

#include <fstream>
#include <sstream>

namespace Neon
{
    std::string File::readFileText(const char *filePath)
    {
        std::ifstream file(filePath);
        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }
}
