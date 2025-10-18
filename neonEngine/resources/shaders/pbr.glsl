#version 460 core

#type vertex
layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inUV;

layout(std140, binding = 0) uniform CameraUniforms
{
    mat4 viewMatrix;
    mat4 projMatrix;
} camera;

layout(std140, binding = 1) uniform ModelUniforms
{
    mat4 matrix;
} model;

layout(location = 0) out vec3 vNormal;
layout(location = 1) out vec2 vUV;
layout(location = 2) out vec3 vFragPos;

void main()
{
    vNormal = inNormal;
    vUV = inUV;
    vec4 fragPos = model.matrix*vec4(inPosition, 1.0);
    vFragPos = fragPos.xyz;
    vec4 camPos = camera.projMatrix*camera.viewMatrix*fragPos;
    gl_Position = camPos;
}

#type fragment
const int MAX_MATERIALS = 32;
const int MAX_POINT_LIGHTS = 32;

layout(location = 0) out vec4 outColor;

layout(std140, binding = 2) uniform MaterialUniforms
{
    float roughness;
    float metanless;
    vec4 albedo;
    bool useAlbedoTexture;
} material;

struct PointLight
{
    vec3 position;
    float power;
    vec3 color;
};

layout(std140, binding = 3) uniform PointLightUniforms
{
    int count;
    PointLight[MAX_POINT_LIGHTS] lights;
} pointLights;

layout(std140, binding = 4) uniform DebugUniforms
{
    bool uvs;
    bool normals;
} debug;

layout(binding = 1) uniform sampler2D albedoTexture;

layout(location = 0) in vec3 vNormal;
layout(location = 1) in vec2 vUV;
layout(location = 2) in vec3 vFragPos;



void main()
{
    if(debug.uvs)
    {
        outColor = vec4(vUV, 0.0f, 1.0f);
        return;
    }

    if(debug.normals)
    {
        outColor = vec4(vNormal * 0.5 + 0.5, 1.0f);
        return;
    }

    vec3 diffuseLight = vec3(0.0);

    for(int i = 0; i < pointLights.count; i++)
    {
        PointLight light = pointLights.lights[i];
        float dist = length(vFragPos - light.position);
        vec3 lightDir = light.position-vFragPos;

        diffuseLight += light.color*(1/dist)*light.power*dot(lightDir, vNormal);
    }

    diffuseLight = max(diffuseLight, vec3(0.2));

    vec4 albedo = material.albedo;

    if(material.useAlbedoTexture)
    {
        albedo *= texture(albedoTexture, vUV);
    }

    outColor = albedo*vec4(diffuseLight, 1.0);
}
