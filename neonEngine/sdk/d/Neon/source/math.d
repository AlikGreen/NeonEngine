module math;


struct Vec3
{
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
}

struct Mat4
{
    float[16] data = [
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    ];
}
