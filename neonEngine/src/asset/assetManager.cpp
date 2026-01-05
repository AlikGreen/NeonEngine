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

    std::stringstream AssetManager::serialize()
    {
        std::stringstream ss;
        const std::string str = "hello____";
        ss << str;
        return ss;
    }

    void AssetManager::deserialize(std::stringstream& stream)
    {
        std::string str(9, '\0');
        stream.read(&str[0], 9);
        Log::info("Image deserialized: {}", str);
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
