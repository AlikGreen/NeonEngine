#version 460 core

#type vertex
layout(location = 0) in vec2 inPosition;
layout(location = 0) out vec3 vWorldDir;

layout(std140, binding = 0) uniform CameraUniforms
{
    mat4 viewMatrix;
    mat4 projMatrix;
} camera;

void main()
{
    gl_Position = vec4(inPosition, 0.0, 1.0);


    mat4 invProj = inverse(camera.projMatrix);
    mat3 viewRot = mat3(camera.viewMatrix);
    mat3 invViewRot = transpose(viewRot);
    vec4 viewPos = invProj * vec4(inPosition, 1.0, 1.0);

    vWorldDir = invViewRot * viewPos.xyz;
}

#type fragment
layout(location = 0) out vec4 outColor;

layout(binding = 0) uniform samplerCube skyboxTexture;

layout(location = 0) in vec3 vWorldDir;

void main()
{
    // 1. Normalize the interpolated direction
    vec3 dir = normalize(vWorldDir);

    // 2. Sample HDR texture
    vec3 envColor = texture(skyboxTexture, dir).rgb;

    // 3. Tone Mapping (Reinhard)
    envColor = envColor / (envColor + vec3(1.0));

    // 4. Gamma Correction
    envColor = pow(envColor, vec3(1.0 / 2.2));

    outColor = vec4(1.0, 0.0, 0.0, 1.0);
}