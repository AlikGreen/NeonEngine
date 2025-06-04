#pragma once

namespace Neon
{
enum class TextureFormat
{
    Invalid,

    // Unsigned Normalized Float
    A8Unorm,
    R8Unorm,
    R8G8Unorm,
    R8G8B8A8Unorm,
    R16Unorm,
    R16G16Unorm,
    R16G16B16A16Unorm,
    R10G10B10A2Unorm,
    B5G6R5Unorm,
    B5G5R5A1Unorm,
    B4G4R4A4Unorm,
    B8G8R8A8Unorm,

    // Compressed UNORM
    BC1RgbaUnorm,
    BC2RgbaUnorm,
    BC3RgbaUnorm,
    BC4RUnorm,
    BC5RgUnorm,
    BC7RgbaUnorm,

    // Compressed float
    BC6HRgbFloat,
    BC6HRgbUfloat,

    // Signed Normalized
    R8Snorm,
    R8G8Snorm,
    R8G8B8A8Snorm,
    R16Snorm,
    R16G16Snorm,
    R16G16B16A16Snorm,

    // Float
    R16Float,
    R16G16Float,
    R16G16B16A16Float,
    R32Float,
    R32G32Float,
    R32G32B32A32Float,
    R11G11B10Ufloat,

    // Unsigned Int
    R8Uint,
    R8G8Uint,
    R8G8B8A8Uint,
    R16Uint,
    R16G16Uint,
    R16G16B16A16Uint,
    R32Uint,
    R32G32Uint,
    R32G32B32A32Uint,

    // Signed Int
    R8Int,
    R8G8Int,
    R8G8B8A8Int,
    R16Int,
    R16G16Int,
    R16G16B16A16Int,
    R32Int,
    R32G32Int,
    R32G32B32A32Int,

    // sRGB
    R8G8B8A8UnormSrgb,
    B8G8R8A8UnormSrgb,

    // Compressed sRGB
    BC1RgbaUnormSrgb,
    BC2RgbaUnormSrgb,
    BC3RgbaUnormSrgb,
    BC7RgbaUnormSrgb,

    // Depth/Stencil
    D16Unorm,
    D24Unorm,
    D32Float,
    D24UnormS8Uint,
    D32FloatS8Uint,

    // ASTC
    ASTC4x4Unorm,  ASTC5x4Unorm,  ASTC5x5Unorm,  ASTC6x5Unorm,
    ASTC6x6Unorm,  ASTC8x5Unorm,  ASTC8x6Unorm,  ASTC8x8Unorm,
    ASTC10x5Unorm, ASTC10x6Unorm, ASTC10x8Unorm, ASTC10x10Unorm,
    ASTC12x10Unorm,ASTC12x12Unorm,

    ASTC4x4UnormSrgb,  ASTC5x4UnormSrgb,  ASTC5x5UnormSrgb,  ASTC6x5UnormSrgb,
    ASTC6x6UnormSrgb,  ASTC8x5UnormSrgb,  ASTC8x6UnormSrgb,  ASTC8x8UnormSrgb,
    ASTC10x5UnormSrgb, ASTC10x6UnormSrgb, ASTC10x8UnormSrgb, ASTC10x10UnormSrgb,
    ASTC12x10UnormSrgb,ASTC12x12UnormSrgb,

    ASTC4x4Float,  ASTC5x4Float,  ASTC5x5Float,  ASTC6x5Float,
    ASTC6x6Float,  ASTC8x5Float,  ASTC8x6Float,  ASTC8x8Float,
    ASTC10x5Float, ASTC10x6Float, ASTC10x8Float, ASTC10x10Float,
    ASTC12x10Float,ASTC12x12Float
};
}
