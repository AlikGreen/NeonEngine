module main

// Import printf directly from C standard library for reliable debugging
#include <stdio.h>
fn C.printf(format &char, ...voidptr) int

type CCallback = fn (int)

__global (
    g_cb voidptr
)

@[export: 'register_callback']
pub fn register_callback(cb voidptr) {
    // Print the address we received to verify connection
    unsafe
    {
        C.printf(c'[V-DLL] Registered callback at address: %p\n', cb)
    }
    g_cb = cb
}

@[export: 'invoke_callback']
pub fn invoke_callback()
{
    if g_cb == voidptr(0)
    {
        unsafe { C.printf(c'[V-DLL] Error: Callback is null\n') }
        return
    }

    unsafe
    {
        C.printf(c'[V-DLL] Invoking callback...\n')
        // Explicit cast inside unsafe block
        cb := CCallback(g_cb)
        cb(42)
    }
}