module scene_management.components;
public import math;


struct ComponentsCallbacks
{
    extern (C) const(char)* function(void*) Tag_getName;
    extern (C) void function(void*, const(char)*) Tag_setName;
}

struct NativeComponent
{
    private static ComponentsCallbacks callbacks;

    public static void setCallbacks(ComponentsCallbacks callbacks)
    {
        this.callbacks = callbacks;
    }

    public static ComponentsCallbacks getCallbacks()
    {
        return callbacks;
    }

    string cppTypeName;
}

@NativeComponent("Tag")
struct Tag
{
    private ubyte[56] _data;

    @property string name()
    {
        import std.string : fromStringz;

        const(char)* cstr = NativeComponent.getCallbacks().Tag_getName(cast(void*)&this);
        return cstr ? fromStringz(cstr).idup : "";
    }

    @property void name(string value)
    {
        import std.string : toStringz;

        const(char)* cstr = toStringz(value);
        NativeComponent.getCallbacks().Tag_setName(cast(void*)&this, cstr);
    }
}

@NativeComponent("Camera")
struct Camera
{
    private ubyte[304] _data;
}

@NativeComponent("Transform")
struct Transform
{
    // Must match C++ layout exactly
    private Vec3 _position;
    private Vec3 _rotation;
    private Vec3 _scale = Vec3(1.0f, 1.0f, 1.0f);

    private bool _dirty = true;
    private Mat4 _cachedLocalMatrix;
    private Mat4 _cachedLocalRotationMatrix;

    @property ref Vec3 position()
    {
        _dirty = true;
        return _position;
    }

    @property void position(Vec3 pos)
    {
        _position = pos;
        _dirty = true;
    }

    // Rotation property
    @property ref Vec3 rotation()
    {
        _dirty = true;
        return _rotation;
    }

    @property void rotation(Vec3 rot)
    {
        _rotation = rot;
        _dirty = true;
    }

    // Scale property
    @property ref Vec3 scale()
    {
        _dirty = true;
        return _scale;
    }

    @property void scale(Vec3 scl)
    {
        _scale = scl;
        _dirty = true;
    }

    // Methods
    void rotate(Vec3 rot)
    {
        _rotation.x += rot.x;
        _rotation.y += rot.y;
        _rotation.z += rot.z;
        _dirty = true;
    }

    void translate(Vec3 translation)
    {
        _position.x += translation.x;
        _position.y += translation.y;
        _position.z += translation.z;
        _dirty = true;
    }

    void setLocalMatrix(Mat4 transform)
    {
        _cachedLocalMatrix = transform;
        _dirty = false; // Setting matrix directly means it's not dirty
    }
}
