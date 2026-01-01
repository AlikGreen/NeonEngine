#type vertex
layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inUV;

layout(location = 0) out vec3 vWorldDir;

layout(std140, binding = 0) uniform CameraUniforms
{
    mat4 viewMatrix;
    mat4 projMatrix;
} camera;

void main()
{
    gl_Position = vec4(inPosition, 1.0);


    mat4 invProj = inverse(camera.projMatrix);
    mat3 viewRot = mat3(camera.viewMatrix);
    mat3 invViewRot = transpose(viewRot);
    vec4 viewPos = invProj * vec4(inPosition.xy, 1.0, 1.0);

    vWorldDir = invViewRot * viewPos.xyz;
}

#type fragment
layout(location = 0) out vec4 outColor;

layout(binding = 0) uniform sampler2D skyboxTexture;

layout(location = 0) in vec3 vWorldDir;

const float PI = 3.14159265359;

vec2 dirToEquirectUv(vec3 dir)
{
    dir = normalize(dir);

    float phi = atan(dir.z, dir.x);
    float theta = asin(clamp(dir.y, -1.0, 1.0));

    float u = phi / (2.0 * PI) + 0.5;
    float v = 0.5 - (theta / PI);

    return vec2(u, v);
}


void main()
{
    vec3 dir = normalize(vWorldDir);

    vec2 uv = dirToEquirectUv(dir);
    vec3 envColor = texture(skyboxTexture, uv).rgb;

    envColor = envColor / (envColor + vec3(1.0));
    envColor = pow(envColor, vec3(1.0 / 2.2));

    outColor = vec4(envColor, 1.0);
}