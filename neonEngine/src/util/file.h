#pragma once
#include <string>

namespace Neon
{
class File
{
public:
    static std::string readFileText(const char* filePath);
    static std::string getFileExtension(const std::string& filePath);
};
}
