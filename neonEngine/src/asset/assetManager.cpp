#include "assetManager.h"

#include "core/engine.h"

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

    std::vector<AssetHandle> AssetManager::getAllAssetHandles()
    {
        return assetHandles;
    }

    std::string AssetManager::getName(const AssetHandle handle)
    {
        return assets.at(handle).name;
    }

    std::type_index AssetManager::getType(const AssetHandle handle) const
    {
        return assets.at(handle).type;
    }
}
