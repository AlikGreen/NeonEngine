import std.stdio;
import std.format;
import std.algorithm;

import log;
import input;
import registry;

alias GetRegistryFn = extern (C) void* function();

struct Callbacks
{
    GetRegistryFn getRegistry = null;

    InputCallbacks* inputCallbacks = null;
    RegistryCallbacks* registryCallbacks = null;
    TagCallbacks* tagCallbacks = null;
}

Callbacks g_callbacks;

struct Position
{
    float x;
    float y;
}

struct Velocity
{
    float x;
    float y;
}

import core.runtime;

version(Windows)
{
    import core.sys.windows.dll;
    
    mixin SimpleDllMain;  // auto-initializes D runtime
}



extern (C) export void native_registerCallbacks(Callbacks* cbStruct)
{
    try 
    {
        if (cbStruct == null)
        {
            writeln("cbStruct is NULL!");
            return;
        }

        g_callbacks = *cbStruct;

        Registry.setCallbacks(*g_callbacks.registryCallbacks);
        Input.setCallbacks(*g_callbacks.inputCallbacks);
        Tag.setCallbacks(*g_callbacks.tagCallbacks);
    }
    catch (Throwable t) 
    {
        import std.stdio : stderr;
        stderr.writeln("=====================================");
        stderr.writeln("D SCRIPT ERROR:");
        stderr.writeln(t.msg);
        stderr.writeln("Stack trace:");
        stderr.writeln(t.info); 
        stderr.writeln("=====================================");
    }
}

extern (C) export void native_update()
{
    import core.stdc.stdio : printf;
    try 
    {
        void* registryHandle = g_callbacks.getRegistry();
        Registry registry = new Registry(registryHandle);
        auto view = registry.view!(Transform, Camera)();

        int count = 0;

        foreach (entity, transform, camera; view)
        {
            if(count != 0) continue;
            count++;

            if(Input.isKeyHeld(KeyCode.w))
            {
                transform.position.z += 0.01f;
                printf("[%d] entity_id: %zu\n", count, entity);
                printf("Position: z=%f\n", transform.position.z);
            }
        }
    }
    catch (Throwable t) 
    {
        import std.stdio : stderr;
        stderr.writeln("=====================================");
        stderr.writeln("D SCRIPT ERROR:");
        stderr.writeln(t.msg);
        stderr.writeln("Stack trace:");
        stderr.writeln(t.info); 
        stderr.writeln("=====================================");
    }
}
