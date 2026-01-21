module registry;
import std.stdio;
import std.traits;
public import components;

private struct RegistryComponentPack
{
    size_t entity_id;
    size_t component_count;
    void* components;
}

private alias GetCppTypeHash = extern (C) size_t function(const char*);

private alias RegistryRegisterTypeFn = extern (C) void function(void*, size_t, size_t, size_t);
private alias RegistryGetViewFn = extern (C) void* function(void*, void*, size_t);

private alias RegistryCreateEntityFn = extern (C) size_t function(void*);
private alias RegistryEmplaceComponentFn = extern (C) void* function(void*, size_t, size_t, void*);

private alias ViewGetAtFn = extern (C) RegistryComponentPack* function(void*, size_t);
private alias ViewGetSizeFn = extern (C) size_t function(void*);

struct RegistryCallbacks
{
    GetCppTypeHash getCppTypeHash = null;
    
    RegistryRegisterTypeFn registerType = null;
    RegistryGetViewFn getView = null;
    RegistryCreateEntityFn createEntity = null;
    RegistryEmplaceComponentFn emplaceComponent = null;

    ViewGetAtFn viewGetAt = null;
    ViewGetSizeFn viewGetSize = null;
}

import std.typecons : tuple, Tuple;

string generateViewAt(Types...)()
{
    string s;
    s ~= "auto pack = cast(RegistryComponentPack*)Registry.callbacks.viewGetAt(ptr, index);\n";
    s ~= "size_t entity = pack.entity_id;\n";
    s ~= "void** comps = cast(void**)pack.components;\n";
    s ~= "return tuple(entity";
    static foreach (idx, T; Types)
    {
        s ~= ", cast(Types[" ~ idx.stringof ~ "]* )comps[" ~ idx.stringof ~ "]";
    }
    s ~= ");\n";
    return s;
}

class Registry
{
    static RegistryCallbacks callbacks;
    
    bool[size_t] registeredTypes;
    void* handle;

    public this(void* handle)
    {
        this.handle = handle;
        registeredTypes = new bool[size_t];
    }

    public static void setCallbacks(RegistryCallbacks callbacks)
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

    size_t ensureRegistered(T)()
    {
        static if (hasUDA!(T, NativeComponent))
        {
            enum attr = getUDAs!(T, NativeComponent)[0];
            
            static size_t id = 0;
            if (id == 0)
            {
                import std.string : toStringz;
                id = callbacks.getCppTypeHash(toStringz(attr.cppTypeName));
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
        return *cast(T*)ptr;
    }


    public auto view(Types...)()
    {
        size_t[] types = new size_t[Types.length];
        static foreach (i, T; Types)
        {
            types[i] = ensureRegistered!T();
        }

        void* ptr = callbacks.getView(handle, types.ptr, types.length);
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
        _size = Registry.callbacks.viewGetSize(ptr);
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