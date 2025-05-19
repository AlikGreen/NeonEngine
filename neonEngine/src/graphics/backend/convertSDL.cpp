#include "convertSDL.h"

#include <SDL3/SDL_gpu.h>

namespace Neon
{
    SDL_GPUStoreOp ConvertSDL::storeOpToSDL(const StoreOperation storeOp)
    {
        switch (storeOp)
        {
            case StoreOperation::Store:
                return SDL_GPU_STOREOP_STORE;
            case StoreOperation::Resolve:
                return SDL_GPU_STOREOP_RESOLVE;
            case StoreOperation::DontCare:
                return SDL_GPU_STOREOP_DONT_CARE;
            case StoreOperation::ResolveAndStore:
                return SDL_GPU_STOREOP_RESOLVE_AND_STORE;
        }
        return SDL_GPU_STOREOP_DONT_CARE;
    }

    SDL_GPULoadOp ConvertSDL::loadOpToSDL(const LoadOperation loadOp)
    {
        switch (loadOp)
        {
            case LoadOperation::Clear:
                return SDL_GPU_LOADOP_CLEAR;
            case LoadOperation::Load:
                return SDL_GPU_LOADOP_LOAD;
            case LoadOperation::DontCare:
                return SDL_GPU_LOADOP_DONT_CARE;
        }

        return SDL_GPU_LOADOP_DONT_CARE;
    }

    TextureFormat ConvertSDL::SDLToTextureFormat(const SDL_GPUTextureFormat format)
    {
        switch (format)
        {
        #define TF_MAP(sdl, camel) case SDL_GPU_TEXTUREFORMAT_##sdl: return TextureFormat::camel;

            TF_MAP(INVALID, Invalid)

            TF_MAP(A8_UNORM, A8Unorm)
            TF_MAP(R8_UNORM, R8Unorm)
            TF_MAP(R8G8_UNORM, R8G8Unorm)
            TF_MAP(R8G8B8A8_UNORM, R8G8B8A8Unorm)
            TF_MAP(R16_UNORM, R16Unorm)
            TF_MAP(R16G16_UNORM, R16G16Unorm)
            TF_MAP(R16G16B16A16_UNORM, R16G16B16A16Unorm)
            TF_MAP(R10G10B10A2_UNORM, R10G10B10A2Unorm)
            TF_MAP(B5G6R5_UNORM, B5G6R5Unorm)
            TF_MAP(B5G5R5A1_UNORM, B5G5R5A1Unorm)
            TF_MAP(B4G4R4A4_UNORM, B4G4R4A4Unorm)
            TF_MAP(B8G8R8A8_UNORM, B8G8R8A8Unorm)

            TF_MAP(BC1_RGBA_UNORM, BC1RgbaUnorm)
            TF_MAP(BC2_RGBA_UNORM, BC2RgbaUnorm)
            TF_MAP(BC3_RGBA_UNORM, BC3RgbaUnorm)
            TF_MAP(BC4_R_UNORM, BC4RUnorm)
            TF_MAP(BC5_RG_UNORM, BC5RgUnorm)
            TF_MAP(BC7_RGBA_UNORM, BC7RgbaUnorm)

            TF_MAP(BC6H_RGB_FLOAT, BC6HRgbFloat)
            TF_MAP(BC6H_RGB_UFLOAT, BC6HRgbUfloat)

            TF_MAP(R8_SNORM, R8Snorm)
            TF_MAP(R8G8_SNORM, R8G8Snorm)
            TF_MAP(R8G8B8A8_SNORM, R8G8B8A8Snorm)
            TF_MAP(R16_SNORM, R16Snorm)
            TF_MAP(R16G16_SNORM, R16G16Snorm)
            TF_MAP(R16G16B16A16_SNORM, R16G16B16A16Snorm)

            TF_MAP(R16_FLOAT, R16Float)
            TF_MAP(R16G16_FLOAT, R16G16Float)
            TF_MAP(R16G16B16A16_FLOAT, R16G16B16A16Float)
            TF_MAP(R32_FLOAT, R32Float)
            TF_MAP(R32G32_FLOAT, R32G32Float)
            TF_MAP(R32G32B32A32_FLOAT, R32G32B32A32Float)
            TF_MAP(R11G11B10_UFLOAT, R11G11B10Ufloat)

            TF_MAP(R8_UINT, R8Uint)
            TF_MAP(R8G8_UINT, R8G8Uint)
            TF_MAP(R8G8B8A8_UINT, R8G8B8A8Uint)
            TF_MAP(R16_UINT, R16Uint)
            TF_MAP(R16G16_UINT, R16G16Uint)
            TF_MAP(R16G16B16A16_UINT, R16G16B16A16Uint)
            TF_MAP(R32_UINT, R32Uint)
            TF_MAP(R32G32_UINT, R32G32Uint)
            TF_MAP(R32G32B32A32_UINT, R32G32B32A32Uint)

            TF_MAP(R8_INT, R8Int)
            TF_MAP(R8G8_INT, R8G8Int)
            TF_MAP(R8G8B8A8_INT, R8G8B8A8Int)
            TF_MAP(R16_INT, R16Int)
            TF_MAP(R16G16_INT, R16G16Int)
            TF_MAP(R16G16B16A16_INT, R16G16B16A16Int)
            TF_MAP(R32_INT, R32Int)
            TF_MAP(R32G32_INT, R32G32Int)
            TF_MAP(R32G32B32A32_INT, R32G32B32A32Int)

            TF_MAP(R8G8B8A8_UNORM_SRGB, R8G8B8A8UnormSrgb)
            TF_MAP(B8G8R8A8_UNORM_SRGB, B8G8R8A8UnormSrgb)

            TF_MAP(BC1_RGBA_UNORM_SRGB, BC1RgbaUnormSrgb)
            TF_MAP(BC2_RGBA_UNORM_SRGB, BC2RgbaUnormSrgb)
            TF_MAP(BC3_RGBA_UNORM_SRGB, BC3RgbaUnormSrgb)
            TF_MAP(BC7_RGBA_UNORM_SRGB, BC7RgbaUnormSrgb)

            TF_MAP(D16_UNORM, D16Unorm)
            TF_MAP(D24_UNORM, D24Unorm)
            TF_MAP(D32_FLOAT, D32Float)
            TF_MAP(D24_UNORM_S8_UINT, D24UnormS8Uint)
            TF_MAP(D32_FLOAT_S8_UINT, D32FloatS8Uint)

            TF_MAP(ASTC_4x4_UNORM, ASTC4x4Unorm)
            TF_MAP(ASTC_5x4_UNORM, ASTC5x4Unorm)
            TF_MAP(ASTC_5x5_UNORM, ASTC5x5Unorm)
            TF_MAP(ASTC_6x5_UNORM, ASTC6x5Unorm)
            TF_MAP(ASTC_6x6_UNORM, ASTC6x6Unorm)
            TF_MAP(ASTC_8x5_UNORM, ASTC8x5Unorm)
            TF_MAP(ASTC_8x6_UNORM, ASTC8x6Unorm)
            TF_MAP(ASTC_8x8_UNORM, ASTC8x8Unorm)
            TF_MAP(ASTC_10x5_UNORM, ASTC10x5Unorm)
            TF_MAP(ASTC_10x6_UNORM, ASTC10x6Unorm)
            TF_MAP(ASTC_10x8_UNORM, ASTC10x8Unorm)
            TF_MAP(ASTC_10x10_UNORM,ASTC10x10Unorm)
            TF_MAP(ASTC_12x10_UNORM,ASTC12x10Unorm)
            TF_MAP(ASTC_12x12_UNORM,ASTC12x12Unorm)

            TF_MAP(ASTC_4x4_UNORM_SRGB, ASTC4x4UnormSrgb)
            TF_MAP(ASTC_5x4_UNORM_SRGB, ASTC5x4UnormSrgb)
            TF_MAP(ASTC_5x5_UNORM_SRGB, ASTC5x5UnormSrgb)
            TF_MAP(ASTC_6x5_UNORM_SRGB, ASTC6x5UnormSrgb)
            TF_MAP(ASTC_6x6_UNORM_SRGB, ASTC6x6UnormSrgb)
            TF_MAP(ASTC_8x5_UNORM_SRGB, ASTC8x5UnormSrgb)
            TF_MAP(ASTC_8x6_UNORM_SRGB, ASTC8x6UnormSrgb)
            TF_MAP(ASTC_8x8_UNORM_SRGB, ASTC8x8UnormSrgb)
            TF_MAP(ASTC_10x5_UNORM_SRGB,ASTC10x5UnormSrgb)
            TF_MAP(ASTC_10x6_UNORM_SRGB,ASTC10x6UnormSrgb)
            TF_MAP(ASTC_10x8_UNORM_SRGB,ASTC10x8UnormSrgb)
            TF_MAP(ASTC_10x10_UNORM_SRGB,ASTC10x10UnormSrgb)
            TF_MAP(ASTC_12x10_UNORM_SRGB,ASTC12x10UnormSrgb)
            TF_MAP(ASTC_12x12_UNORM_SRGB,ASTC12x12UnormSrgb)

            TF_MAP(ASTC_4x4_FLOAT,  ASTC4x4Float)
            TF_MAP(ASTC_5x4_FLOAT,  ASTC5x4Float)
            TF_MAP(ASTC_5x5_FLOAT,  ASTC5x5Float)
            TF_MAP(ASTC_6x5_FLOAT,  ASTC6x5Float)
            TF_MAP(ASTC_6x6_FLOAT,  ASTC6x6Float)
            TF_MAP(ASTC_8x5_FLOAT,  ASTC8x5Float)
            TF_MAP(ASTC_8x6_FLOAT,  ASTC8x6Float)
            TF_MAP(ASTC_8x8_FLOAT,  ASTC8x8Float)
            TF_MAP(ASTC_10x5_FLOAT, ASTC10x5Float)
            TF_MAP(ASTC_10x6_FLOAT, ASTC10x6Float)
            TF_MAP(ASTC_10x8_FLOAT, ASTC10x8Float)
            TF_MAP(ASTC_10x10_FLOAT,ASTC10x10Float)
            TF_MAP(ASTC_12x10_FLOAT,ASTC12x10Float)
            TF_MAP(ASTC_12x12_FLOAT,ASTC12x12Float)

        #undef TF_MAP

        default: return TextureFormat::Invalid;
        }
    }

    SDL_GPUTextureFormat ConvertSDL::textureFormatToSDL(const TextureFormat format)
    {
        switch (format)
        {
        #define BACK_MAP(camel, sdl) case TextureFormat::camel: return SDL_GPU_TEXTUREFORMAT_##sdl;

            BACK_MAP(Invalid, INVALID)

            BACK_MAP(A8Unorm, A8_UNORM)
            BACK_MAP(R8Unorm, R8_UNORM)
            BACK_MAP(R8G8Unorm, R8G8_UNORM)
            BACK_MAP(R8G8B8A8Unorm, R8G8B8A8_UNORM)
            BACK_MAP(R16Unorm, R16_UNORM)
            BACK_MAP(R16G16Unorm, R16G16_UNORM)
            BACK_MAP(R16G16B16A16Unorm, R16G16B16A16_UNORM)
            BACK_MAP(R10G10B10A2Unorm, R10G10B10A2_UNORM)
            BACK_MAP(B5G6R5Unorm, B5G6R5_UNORM)
            BACK_MAP(B5G5R5A1Unorm, B5G5R5A1_UNORM)
            BACK_MAP(B4G4R4A4Unorm, B4G4R4A4_UNORM)
            BACK_MAP(B8G8R8A8Unorm, B8G8R8A8_UNORM)

            BACK_MAP(BC1RgbaUnorm, BC1_RGBA_UNORM)
            BACK_MAP(BC2RgbaUnorm, BC2_RGBA_UNORM)
            BACK_MAP(BC3RgbaUnorm, BC3_RGBA_UNORM)
            BACK_MAP(BC4RUnorm, BC4_R_UNORM)
            BACK_MAP(BC5RgUnorm, BC5_RG_UNORM)
            BACK_MAP(BC7RgbaUnorm, BC7_RGBA_UNORM)

            BACK_MAP(BC6HRgbFloat, BC6H_RGB_FLOAT)
            BACK_MAP(BC6HRgbUfloat, BC6H_RGB_UFLOAT)

            BACK_MAP(R8Snorm, R8_SNORM)
            BACK_MAP(R8G8Snorm, R8G8_SNORM)
            BACK_MAP(R8G8B8A8Snorm, R8G8B8A8_SNORM)
            BACK_MAP(R16Snorm, R16_SNORM)
            BACK_MAP(R16G16Snorm, R16G16_SNORM)
            BACK_MAP(R16G16B16A16Snorm, R16G16B16A16_SNORM)

            BACK_MAP(R16Float, R16_FLOAT)
            BACK_MAP(R16G16Float, R16G16_FLOAT)
            BACK_MAP(R16G16B16A16Float, R16G16B16A16_FLOAT)
            BACK_MAP(R32Float, R32_FLOAT)
            BACK_MAP(R32G32Float, R32G32_FLOAT)
            BACK_MAP(R32G32B32A32Float, R32G32B32A32_FLOAT)
            BACK_MAP(R11G11B10Ufloat, R11G11B10_UFLOAT)

            BACK_MAP(R8Uint, R8_UINT)
            BACK_MAP(R8G8Uint, R8G8_UINT)
            BACK_MAP(R8G8B8A8Uint, R8G8B8A8_UINT)
            BACK_MAP(R16Uint, R16_UINT)
            BACK_MAP(R16G16Uint, R16G16_UINT)
            BACK_MAP(R16G16B16A16Uint, R16G16B16A16_UINT)
            BACK_MAP(R32Uint, R32_UINT)
            BACK_MAP(R32G32Uint, R32G32_UINT)
            BACK_MAP(R32G32B32A32Uint, R32G32B32A32_UINT)

            BACK_MAP(R8Int, R8_INT)
            BACK_MAP(R8G8Int, R8G8_INT)
            BACK_MAP(R8G8B8A8Int, R8G8B8A8_INT)
            BACK_MAP(R16Int, R16_INT)
            BACK_MAP(R16G16Int, R16G16_INT)
            BACK_MAP(R16G16B16A16Int, R16G16B16A16_INT)
            BACK_MAP(R32Int, R32_INT)
            BACK_MAP(R32G32Int, R32G32_INT)
            BACK_MAP(R32G32B32A32Int, R32G32B32A32_INT)

            BACK_MAP(R8G8B8A8UnormSrgb, R8G8B8A8_UNORM_SRGB)
            BACK_MAP(B8G8R8A8UnormSrgb, B8G8R8A8_UNORM_SRGB)

            BACK_MAP(BC1RgbaUnormSrgb, BC1_RGBA_UNORM_SRGB)
            BACK_MAP(BC2RgbaUnormSrgb, BC2_RGBA_UNORM_SRGB)
            BACK_MAP(BC3RgbaUnormSrgb, BC3_RGBA_UNORM_SRGB)
            BACK_MAP(BC7RgbaUnormSrgb, BC7_RGBA_UNORM_SRGB)

            BACK_MAP(D16Unorm, D16_UNORM)
            BACK_MAP(D24Unorm, D24_UNORM)
            BACK_MAP(D32Float, D32_FLOAT)
            BACK_MAP(D24UnormS8Uint, D24_UNORM_S8_UINT)
            BACK_MAP(D32FloatS8Uint, D32_FLOAT_S8_UINT)

            BACK_MAP(ASTC4x4Unorm, ASTC_4x4_UNORM)
            BACK_MAP(ASTC5x4Unorm, ASTC_5x4_UNORM)
            BACK_MAP(ASTC5x5Unorm, ASTC_5x5_UNORM)
            BACK_MAP(ASTC6x5Unorm, ASTC_6x5_UNORM)
            BACK_MAP(ASTC6x6Unorm, ASTC_6x6_UNORM)
            BACK_MAP(ASTC8x5Unorm, ASTC_8x5_UNORM)
            BACK_MAP(ASTC8x6Unorm, ASTC_8x6_UNORM)
            BACK_MAP(ASTC8x8Unorm, ASTC_8x8_UNORM)
            BACK_MAP(ASTC10x5Unorm, ASTC_10x5_UNORM)
            BACK_MAP(ASTC10x6Unorm, ASTC_10x6_UNORM)
            BACK_MAP(ASTC10x8Unorm, ASTC_10x8_UNORM)
            BACK_MAP(ASTC10x10Unorm, ASTC_10x10_UNORM)
            BACK_MAP(ASTC12x10Unorm, ASTC_12x10_UNORM)
            BACK_MAP(ASTC12x12Unorm, ASTC_12x12_UNORM)

            BACK_MAP(ASTC4x4UnormSrgb, ASTC_4x4_UNORM_SRGB)
            BACK_MAP(ASTC5x4UnormSrgb, ASTC_5x4_UNORM_SRGB)
            BACK_MAP(ASTC5x5UnormSrgb, ASTC_5x5_UNORM_SRGB)
            BACK_MAP(ASTC6x5UnormSrgb, ASTC_6x5_UNORM_SRGB)
            BACK_MAP(ASTC6x6UnormSrgb, ASTC_6x6_UNORM_SRGB)
            BACK_MAP(ASTC8x5UnormSrgb, ASTC_8x5_UNORM_SRGB)
            BACK_MAP(ASTC8x6UnormSrgb, ASTC_8x6_UNORM_SRGB)
            BACK_MAP(ASTC8x8UnormSrgb, ASTC_8x8_UNORM_SRGB)
            BACK_MAP(ASTC10x5UnormSrgb, ASTC_10x5_UNORM_SRGB)
            BACK_MAP(ASTC10x6UnormSrgb, ASTC_10x6_UNORM_SRGB)
            BACK_MAP(ASTC10x8UnormSrgb, ASTC_10x8_UNORM_SRGB)
            BACK_MAP(ASTC10x10UnormSrgb,ASTC_10x10_UNORM_SRGB)
            BACK_MAP(ASTC12x10UnormSrgb,ASTC_12x10_UNORM_SRGB)
            BACK_MAP(ASTC12x12UnormSrgb,ASTC_12x12_UNORM_SRGB)

            BACK_MAP(ASTC4x4Float, ASTC_4x4_FLOAT)
            BACK_MAP(ASTC5x4Float, ASTC_5x4_FLOAT)
            BACK_MAP(ASTC5x5Float, ASTC_5x5_FLOAT)
            BACK_MAP(ASTC6x5Float, ASTC_6x5_FLOAT)
            BACK_MAP(ASTC6x6Float, ASTC_6x6_FLOAT)
            BACK_MAP(ASTC8x5Float, ASTC_8x5_FLOAT)
            BACK_MAP(ASTC8x6Float, ASTC_8x6_FLOAT)
            BACK_MAP(ASTC8x8Float, ASTC_8x8_FLOAT)
            BACK_MAP(ASTC10x5Float, ASTC_10x5_FLOAT)
            BACK_MAP(ASTC10x6Float, ASTC_10x6_FLOAT)
            BACK_MAP(ASTC10x8Float, ASTC_10x8_FLOAT)
            BACK_MAP(ASTC10x10Float,ASTC_10x10_FLOAT)
            BACK_MAP(ASTC12x10Float,ASTC_12x10_FLOAT)
            BACK_MAP(ASTC12x12Float,ASTC_12x12_FLOAT)

        #undef BACK_MAP

            default:
                return SDL_GPU_TEXTUREFORMAT_INVALID;
        }
    }

    TextureType ConvertSDL::SDLToTextureType(const SDL_GPUTextureType type)
    {
        switch (type)
        {
            case SDL_GPU_TEXTURETYPE_2D:
                return TextureType::Texture2D;
            case SDL_GPU_TEXTURETYPE_2D_ARRAY:
                return TextureType::Texture2DArray;
            case SDL_GPU_TEXTURETYPE_3D:
                return TextureType::Texture3D;
            case SDL_GPU_TEXTURETYPE_CUBE:
                return TextureType::TextureCube;
            case SDL_GPU_TEXTURETYPE_CUBE_ARRAY:
                return TextureType::TextureCubeArray;
            default:
                return TextureType::Texture2D;
        }
    }

    SDL_GPUTextureType ConvertSDL::textureTypeToSDL(const TextureType type)
    {
        switch (type)
        {
            case TextureType::Texture2D:
                return SDL_GPU_TEXTURETYPE_2D;
            case TextureType::Texture2DArray:
                return SDL_GPU_TEXTURETYPE_2D_ARRAY;
            case TextureType::Texture3D:
                return SDL_GPU_TEXTURETYPE_3D;
            case TextureType::TextureCube:
                return SDL_GPU_TEXTURETYPE_CUBE;
            case TextureType::TextureCubeArray:
                return SDL_GPU_TEXTURETYPE_CUBE_ARRAY;
            default:
                return SDL_GPU_TEXTURETYPE_2D;
        }
    }
}
