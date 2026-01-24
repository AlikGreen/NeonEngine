import std.stdio;
import std.format;
import std.algorithm;

import log;
import input;
import system;
import scene_management;

struct ScriptRuntimeInterface
{
    InputCallbacks input;
    EcsCallbacks ecs;
    SceneCallbacks scene;
    ComponentsCallbacks components;
}

ScriptRuntimeInterface g_scriptRuntimeInterface;

import core.runtime;

version (Windows)
{
    import core.sys.windows.dll;
    mixin SimpleDllMain; // auto-initializes D runtime
}

alias UpdateDelegate = void function();
private UpdateDelegate[] pendingUpdates;

System[] discoveredSystems;
void*[] loadedLibs;


void discoverSystems()
{
    auto sysTI = cast(TypeInfo_Class) typeid(System);

    foreach (minfo; ModuleInfo)
    {
        foreach (ti; minfo.localClasses)
        {
            if (ti is null)
                continue;

            if (!sysTI.isBaseOf(ti))
                continue;
            
            bool alreadyLoaded = false;
            foreach (existing; discoveredSystems)
            {
                if (typeid(existing) == ti)
                {
                    alreadyLoaded = true;
                    break;
                }
            }
            
            if (alreadyLoaded)
                continue;
            
            Object created;
            try
            {
                created = ti.create();
            }
            catch (Exception e)
            {
                continue;
            }

            auto s = cast(System) created;
            if (s !is null)
            {
                discoveredSystems ~= s;
            }
        }
    }
}

extern (C) export void native_registerCallbacks(ScriptRuntimeInterface* runtimeInterface)
{
    try
    {
        if (runtimeInterface == null)
        {
            writeln("cbStruct is NULL!");
            return;
        }

        g_scriptRuntimeInterface = *runtimeInterface;
        Log.info("Callbacks size: %s", ScriptRuntimeInterface.sizeof);

        Scene.setCallbacks(g_scriptRuntimeInterface.ecs);
        Input.setCallbacks(g_scriptRuntimeInterface.input);
        NativeComponent.setCallbacks(g_scriptRuntimeInterface.components);
        SceneManager.setCallbacks(g_scriptRuntimeInterface.scene);

        discoverSystems();

        foreach (system; discoveredSystems)
        {
            system.startup();
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

extern (C) export void native_loadLib(const(char)* cpath)
{
    import std.string : fromStringz;
    import std.file : exists, isFile;
    import std.path : absolutePath;
    
    string filepath = fromStringz(cpath).idup;
    
    // Check if file exists
    if (!exists(filepath))
    {
        Log.info("ERROR: File does not exist: %s", filepath);
        Log.info("  Absolute path would be: ", absolutePath(filepath));
        return;
    }
    
    if (!isFile(filepath))
    {
        Log.info("ERROR: Path exists but is not a file: ", filepath);
        return;
    }
    
    Log.info("File exists, attempting to load...");
    
    auto handle = Runtime.loadLibrary(filepath);
    if (handle is null)
    {
        Log.info("ERROR: Failed to load library");
        
        version(Windows)
        {
            import core.sys.windows.windows;
            auto err = GetLastError();
            Log.info("  Windows error code: ", err);
        }

        return;
    }
    
    Log.info("Successfully loaded library!");
    loadedLibs ~= handle;
    discoverSystems();
}

extern (C) export void native_update()
{
    import core.stdc.stdio : printf;

    try
    {
        foreach (system; discoveredSystems)
        {
            system.update();
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
