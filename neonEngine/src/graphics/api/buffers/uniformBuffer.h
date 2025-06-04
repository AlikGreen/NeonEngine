#pragma once
#include "buffer.h"

namespace Neon
{
class UniformBuffer : public Buffer
{
public:
  ~UniformBuffer() override = default;
};
}
