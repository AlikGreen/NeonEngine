module math.vector;

import std.format;


struct Vec3
{
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;

    string toString() const
    {
        return "%s, %s, %s".format(x, y, z);
    }

    alias toString this;
}
