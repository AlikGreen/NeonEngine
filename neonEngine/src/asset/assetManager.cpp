#include "assetManager.h"

#include <iostream>

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

    AssetID AssetManager::generateID()
    {
        {
            return AssetID(nextHandle++);
        }
    }

    bool AssetManager::isValid(const AssetID id) const
    {
        return id.getId() > 0 && id.getId() < nextHandle;
    }

    std::vector<AssetID> AssetManager::getAllAssetIDs()
    {
        return assetHandles;
    }

    AssetMetadata AssetManager::getMetadata(const AssetID handle)
    {
        return assetsMetadata.at(handle);
    }
}
