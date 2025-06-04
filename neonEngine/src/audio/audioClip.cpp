#include "audioClip.h"

#include "debug/assert.h"
#include "debug/logger.h"

namespace Neon
{
    void AudioClip::load(const std::string &filePath)
    {
        const ma_result result = ma_decoder_init_file(filePath.c_str(), nullptr, &decoder);
        Assert::check(result == MA_SUCCESS, "File was not found");
    }

    void AudioClip::serialize(AssetStream &stream)
    {
        throw std::runtime_error("Not implemented");
    }

    void AudioClip::deserialize(AssetStream &stream)
    {
        throw std::runtime_error("Not implemented");
    }
}
