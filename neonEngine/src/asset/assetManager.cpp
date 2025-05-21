#include "assetManager.h"

#include "core/engine.h"

namespace Neon
{
    std::unordered_map<AssetHandle, Ref<Asset>> AssetManager::assets;

    std::string AssetManager::getFullPath(const std::string &filePath)
    {
        const std::array possiblePaths =
        {
            std::filesystem::path(Engine::getInstance()->getConfig().gameResourcesPath)/filePath,
            std::filesystem::path(Engine::getInstance()->getConfig().engineResourcesPath)/filePath,
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
