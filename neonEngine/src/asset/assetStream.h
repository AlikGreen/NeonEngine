#pragma once
#include <cstdint>
#include <cstring>
#include <utility>
#include <vector>

namespace Neon
{
class AssetStream
{
public:
    AssetStream() = default;
    explicit AssetStream(std::vector<uint8_t> bytes)
        : buffer(std::move(bytes))
        {  }

    bool read(void* data, const size_t size)
    {
        if(m_cursor + size > buffer.size())
            return false;

        memcpy(data, buffer.data() + m_cursor, size);
        m_cursor += size;
        return true;
    }

    bool write(const void* data, const size_t size)
    {
        if(m_cursor >= 128000)
            return false;

        auto* byteData = static_cast<const uint8_t*>(data);
        buffer.insert(buffer.end(), byteData, byteData + size);
        m_cursor += size;
        return true;
    }

    template<typename T>
    requires std::is_arithmetic_v<T>
    bool write(const T& val)
    {
        return write(&val, sizeof(T));
    }

    template<typename T>
    requires std::is_arithmetic_v<T>
    bool read(T& out)
    {
        return read(&out, sizeof(T));
    }

    template<typename T>
    bool write(std::vector<T> vector)
    {
        if(!write(vector.size()))
            return false;

        if(!write(vector.data(), sizeof(T)))
            return false;

        return true;
    }

    template<typename T>
    bool read(std::vector<T>& vector)
    {
        size_t size = 0;
        if(!read(size))
            return false;

        void* data = nullptr;
        if(!read(&data, sizeof(T)*size))
            return false;

        vector.resize(size);
        vector.assign(data, data + size);

        return true;
    }

    bool write(const std::string &string)
    {
        if(!write(string.size()))
            return false;

        if(!write(string.data(), string.size()))
            return false;

        return true;
    }

    bool read(std::string& string)
    {
        size_t size = 0;
        if(!read(size))
            return false;

        string.resize(size);

        if(size > 0)
        {
            if(!read(string.data(), size))
                return false;
        }

        return true;
    }

    void setCursorPos(const size_t pos)
    {
        m_cursor = pos;
    }

    [[nodiscard]] std::vector<uint8_t> getBuffer() const
    {
        return buffer;
    }
private:
    size_t m_cursor = 0;
    std::vector<uint8_t> buffer{};
};
}
