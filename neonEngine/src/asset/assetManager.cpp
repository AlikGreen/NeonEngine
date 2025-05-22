#include "assetManager.h"

#include "core/engine.h"
#include "debug/logger.h"

namespace Neon
{
    std::string AssetManager::getFullPath(const std::string &filePath)
    {
        const std::array possiblePaths =
        {
            std::filesystem::path(Engine::getConfig().gameResourcesPath)/filePath,
            std::filesystem::path(Engine::getConfig().engineResourcesPath)/filePath,
        };

        for (const auto& path: possiblePaths)
        {
            if(exists(path))
            {
                return path.string();
            }
        }
        return filePath;
    }
}
