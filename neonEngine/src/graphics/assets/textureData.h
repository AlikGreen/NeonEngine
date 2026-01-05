#pragma once
#include <neonRHI/neonRHI.h>

namespace Neon
{
class TextureData
{
public:
  uint32_t width, height;
  RHI::PixelLayout pixelLayout;
  RHI::PixelType pixelType;
  void* data;
};
}
