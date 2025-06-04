#version 460 core

#type vertex
layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inUV;

layout(std140, binding = 0) uniform VertexUniforms
{
    vec4 uModelMatrix;
};

layout(location = 0) out vec3 outNormal;
layout(location = 1) out vec2 outUV;

void main()
{
    outNormal = inNormal;
    outUV = inUV;
    gl_Position = vec4(inPosition, 1.0)+uModelMatrix;
}

#type fragment
layout(location = 0) out vec4 outColor;

layout(std140, binding = 1) uniform FragmentUniforms
{
    vec4 uTintColor;
};

layout(location = 0) in vec3 outNormal;
layout(location = 1) in vec2 outUV;


void main()
{
    outColor = uTintColor;
}

