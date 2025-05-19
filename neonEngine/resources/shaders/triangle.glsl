#type vertex
#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inUV;

layout(set = 1, binding = 0) uniform VertexUniforms
{
    mat4 uModelMatrix;
};

void main()
{
    gl_Position = uModelMatrix * vec4(inPosition, 1.0);
}

#type fragment
#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) out vec4 outColor;

layout(set = 3, binding = 0) uniform FragmentUniforms
{
    vec4 uTintColor;
};

void main()
{
    outColor = uTintColor;
}

