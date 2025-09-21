#pragma once
#include <cstdint>
#include <string>

namespace Neon
{
    class AssetStream
    {
    public:
        virtual ~AssetStream() = default;

        virtual void read(void* data, size_t size) = 0;
        virtual uint32_t readUint32() = 0;
        virtual float readFloat() = 0;
        virtual std::string readString() = 0;

        virtual void write(const void* data, size_t size) = 0;
        virtual void writeUint32(uint32_t value) = 0;
        virtual void writeFloat(float value) = 0;
        virtual void writeString(const std::string& value) = 0;
    };
}
