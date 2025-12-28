#version 460
#type compute

layout(local_size_x = 16, local_size_y = 16, local_size_z = 1) in;

layout(set = 0, binding = 0) uniform sampler2D uEquirect;
layout(binding = 1, rgba32f) uniform writeonly imageCube uOutCube;

layout(std140, set = 0, binding = 2) uniform Params
{
    int uFaceIndex;
    int uOutSize;
} params;

const float PI = 3.14159265359;

vec3 faceUvToDir(int face, vec2 uv)
{
    // Standard OpenGL Cubemap orientation
    // Face 0 (+X), 1 (-X), 2 (+Y), 3 (-Y), 4 (+Z), 5 (-Z)
    if (face == 0) return normalize(vec3( 1.0,  uv.y, -uv.x));
    if (face == 1) return normalize(vec3(-1.0,  uv.y,  uv.x));
    if (face == 2) return normalize(vec3( uv.x,  1.0, -uv.y));
    if (face == 3) return normalize(vec3( uv.x, -1.0,  uv.y));
    if (face == 4) return normalize(vec3( uv.x,  uv.y,  1.0));
    return normalize(vec3(-uv.x,  uv.y, -1.0));
}

vec2 dirToEquirectUv(vec3 dir)
{
    dir = normalize(dir);

    float phi = atan(dir.z, dir.x + 1e-6);
    float theta = asin(clamp(dir.y, -1.0, 1.0));

    float u = phi / (2.0 * PI) + 0.5;

    // FIX 2: Map Up (+Y) to V=0.0 (Top of texture) and Down (-Y) to V=1.0 (Bottom)
    // This assumes your texture has Sky at Row 0 and Ground at Row N.
    float v = 0.5 - (theta / PI);

    return vec2(u, v);
}

void main()
{
    uvec2 gid = gl_GlobalInvocationID.xy;

    if (gid.x >= uint(params.uOutSize) || gid.y >= uint(params.uOutSize))
    {
        return;
    }

    vec2 uv01 = (vec2(gid) + vec2(0.5)) / float(params.uOutSize);

    // FIX 1: Flip the Y coordinate generation.
    // This fixes the "Whole skybox is upside down" issue by inverting the Face-Y axis.
    vec2 uv = uv01 * 2.0 - 1.0;
    uv.y = -uv.y;

    vec3 dir = faceUvToDir(params.uFaceIndex, uv);
    vec2 eqUv = dirToEquirectUv(dir);

    vec4 color = textureLod(uEquirect, eqUv, 0.0);

    imageStore(uOutCube, ivec3(int(gid.x), int(gid.y), params.uFaceIndex), color);
}