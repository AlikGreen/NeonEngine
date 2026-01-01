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

    uint32_t AssetManager::generateID()
    {
        {
            return nextHandle++;
        }
    }

    bool AssetManager::isValid(const AssetID id) const
    {
        return id > 0 && id < nextHandle;
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
