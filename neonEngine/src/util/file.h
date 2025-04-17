#pragma once
#include <string>

namespace Neon
{
class File
{
public:
    static std::string readFileText(const char* filePath);
};
}
