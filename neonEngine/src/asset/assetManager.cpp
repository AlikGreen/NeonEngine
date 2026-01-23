#include "assetManager.h"

#include <iostream>

#include "core/engine.h"

namespace Neon
{
    std::string AssetManager::getFullPath(const std::string &filePath)
    {
        for (const auto& dir: Engine::getConfig().resourcePaths)
        {
            auto filepath = std::filesystem::path(dir)/filePath;
            if(exists(filepath))
            {
                return filepath.string();
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
