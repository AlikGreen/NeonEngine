#version 460 core

#type vertex
layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inUV;

layout(std140, binding = 0) uniform CameraUniforms
{
    mat4 uViewMatrix;
    mat4 uProjMatrix;
};

layout(std140, binding = 1) uniform ModelUniforms
{
    mat4 uModelMatrix;
};

layout(location = 0) out vec3 vNormal;
layout(location = 1) out vec2 vUV;
layout(location = 2) out vec3 vFragPos;

void main()
{
    vNormal = inNormal;
    vUV = inUV;
    vec4 fragPos = uModelMatrix*vec4(inPosition, 1.0);
    vFragPos = fragPos.xyz;
    vec4 camPos = uProjMatrix*uViewMatrix*fragPos;
    gl_Position = camPos;
}

#type fragment
struct Material
{
    float roughness;
    float metanless;
    vec4 albedo;
};

layout(location = 0) out vec4 outColor;

layout(std140, binding = 2) uniform MaterialsUniforms
{
    int materialCount;
    Material[64] materials;
};

struct PointLight
{
    vec3 position;
    float power;
    vec3 color;
};

layout(std140, binding = 3) uniform PointLightUniforms
{
    int pointLightsCount;
    PointLight[32] pointLights;
};

layout(std140, binding = 4) uniform DebugUniforms
{
    bool uDebugUVs;
    bool uDebugNormals;
};

layout(location = 0) in vec3 vNormal;
layout(location = 1) in vec2 vUV;
layout(location = 2) in vec3 vFragPos;

void main()
{
    if(uDebugUVs)
    {
        outColor = vec4(vUV, 0.0f, 1.0f);
        return;
    }

    if(uDebugNormals)
    {
        outColor = vec4(vNormal * 0.5 + 0.5, 1.0f); // Map normal from [-1,1] to [0,1]
        return;
    }

    Material material = materials[0];

    vec3 diffuseLight = vec3(0.0);

    for(int i = 0; i < pointLightsCount; i++)
    {
        vec3 lightPosition = pointLights[i].position;
        float dist = length(vFragPos - lightPosition);
        vec3 lightDir = lightPosition-vFragPos;

        diffuseLight += pointLights[i].color*(1/dist)*pointLights[i].power*dot(lightDir, vNormal);
    }

    diffuseLight = max(diffuseLight, vec3(0.02));

    outColor = material.albedo*vec4(diffuseLight, 0.0);

    //outColor = uAlbedo;
}
