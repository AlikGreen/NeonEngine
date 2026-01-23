module scene;
import std.stdio;
import std.traits;
public import components;

struct EntityComponentData
{
    size_t entity;
    size_t componentCount;
    void* components;
}

struct EcsCallbacks
{
    extern (C) void function(void*, size_t, size_t, size_t) registerComponentType;
    extern (C) size_t function(void*) createEntity;
    extern (C) void* function(void*, size_t, size_t, void*) addComponent;

    extern (C) void* function(void*, size_t* types, size_t count) createView;
    extern (C) size_t function(void*) getViewSize;
    extern (C) EntityComponentData* function(void*, size_t index) getViewEntry;

    extern (C) size_t function(const(char)*) getTypeHash;
}

import std.typecons : tuple, Tuple;

string generateViewAt(Types...)()
{
    string s;
    s ~= "auto pack = cast(EntityComponentData*)Scene.callbacks.getViewEntry(ptr, index);\n";
    s ~= "size_t entity = pack.entity;\n";
    s ~= "void** comps = cast(void**)pack.components;\n";
    s ~= "return tuple(entity";
    static foreach (idx, T; Types)
    {
        s ~= ", cast(Types[" ~ idx.stringof ~ "]* )comps[" ~ idx.stringof ~ "]";
    }
    s ~= ");\n";
    return s;
}

class Scene
{
    static EcsCallbacks callbacks;

    bool[size_t] registeredTypes;
    void* handle;

    public this(void* handle)
    {
        this.handle = handle;
        registeredTypes = new bool[size_t];
    }

    public static void setCallbacks(EcsCallbacks callbacks)
    {
        this.callbacks = callbacks;
    }

    private static size_t fnv1aHash(string s) pure nothrow
    {
        size_t h = size_t(14695981039346656037UL);
        foreach (ubyte c; cast(ubyte[]) s)
        {
            h = (h ^ c) * size_t(1099511628211UL);
        }
        return h;
    }

    private size_t ensureRegistered(T)()
    {
        static if (hasUDA!(T, NativeComponent))
        {
            enum attr = getUDAs!(T, NativeComponent)[0];

            static size_t id = 0;
            if (id == 0)
            {
                import std.string : toStringz;

                id = callbacks.getTypeHash(toStringz(attr.cppTypeName));
            }

            if (!(id in registeredTypes))
            {
                registeredTypes[id] = true;
            }

            return id;
        }
        else
        {
            static size_t id = fnv1aHash(T.stringof);

            if (!(id in registeredTypes))
            {
                callbacks.registerType(handle, id, T.sizeof, T.alignof);
                registeredTypes[id] = true;
            }

            return id;
        }
    }

    public size_t createEntity()
    {
        return callbacks.createEntity(handle);
    }

    public ref T emplace(T)(size_t entityId, T component)
    {
        void* ptr = callbacks.emplaceComponent(handle, entityId, ensureRegistered!T(), &component);
        return *cast(T*) ptr;
    }

    public auto view(Types...)()
    {
        size_t[] types = new size_t[Types.length];
        static foreach (i, T; Types)
        {
            types[i] = ensureRegistered!T();
        }

        void* ptr = callbacks.createView(handle, types.ptr, types.length);
        return View!(Types)(ptr);
    }
}

struct View(Types...)
{
    private size_t i;
    private size_t _size;
    private void* ptr;

    this(void* ptr)
    {
        i = 0;
        this.ptr = ptr;
        _size = Scene.callbacks.getViewSize(ptr);
    }

    @property size_t size()
    {
        return _size;
    }

    auto at(size_t index)
    {
        mixin(generateViewAt!Types);
    }

    bool empty() const
    {
        return i >= _size;
    }

    auto front()
    {
        size_t index = i;
        mixin(generateViewAt!Types);
    }

    void popFront()
    {
        ++i;
    }

    // ForwardRange: return a copy so the range can be saved
    View save()
    {
        return this;
    }
}
