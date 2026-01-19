module neon

struct RegistryComponentPack
{
    entity_id usize
    component_count usize
    components voidptr
};

type IsKeyFn = fn(int) bool
type RegisterTypeFn = fn(voidptr, usize, usize, usize);
type GetRegistryFn = fn() voidptr;
type ViewIterNextFn = fn(voidptr) &RegistryComponentPack;
type GetViewFn = fn(voidptr, voidptr, usize) voidptr;
type CreateEntityFn = fn(voidptr) usize;
type EmplaceComponentFn = fn(voidptr, usize, usize, voidptr);

pub struct Callbacks
{
    is_key_held IsKeyFn = unsafe { nil }
    is_key_pressed IsKeyFn = unsafe { nil }
    is_key_released IsKeyFn = unsafe { nil }

    register_type RegisterTypeFn = unsafe { nil }
    get_registry GetRegistryFn = unsafe { nil }
    view_iter_next ViewIterNextFn = unsafe { nil }
    get_view GetViewFn = unsafe { nil }
    create_entity CreateEntityFn = unsafe { nil }
    emplace_component EmplaceComponentFn = unsafe { nil }
}


__global
(
    g_cb_struct Callbacks
    input Input
    log Log
)

struct View
{
    ptr voidptr
}

fn (mut view View) next() ?RegistryComponentPack
{
    val := g_cb_struct.view_iter_next(view.ptr)
    if val == voidptr(0)
    {
        return none
    }
    return *val
}

struct Position
{
    x f32
    y f32
}

@[export: 'native_register_callbacks']
fn native_register_callbacks(cbStruct &Callbacks)
{
    g_cb_struct = *cbStruct
    log.info('Registered callbacks at address: 0x${cbStruct:X}')

    id := usize(typeof[Position]().idx)
    size := usize(sizeof(Position))
    alignment := usize(sizeof(Position))

    registry := g_cb_struct.get_registry()

    g_cb_struct.register_type(registry, id, size, alignment)
    mut types := []usize{len: 1}
    types[0] = id

    entity1 := g_cb_struct.create_entity(registry)
    entity2 := g_cb_struct.create_entity(registry)

    pos1 := Position{0, 0}
    pos2 := Position{1, 3}

    log.info('Emplacing component with address: 0x${&pos1:X}')
    g_cb_struct.emplace_component(registry, entity1, id, &pos1)
    g_cb_struct.emplace_component(registry, entity2, id, &pos2)

    view_ptr := g_cb_struct.get_view(registry, types.data, usize(types.len))
    view := View{view_ptr}

    for i in view
    {
        unsafe
        {
            // i.components is a pointer to an array of void pointers
            comp_array := &voidptr(i.components)  // Cast to pointer-to-voidptr array
            pos_ptr := comp_array[0]               // Get first element (the actual Position pointer)
            pos := &Position(pos_ptr)              // Cast that to Position pointer
            log.info("c++ iter gave number: ${i.entity_id}, ${pos.x}")
        }
    }
}

@[export: 'native_update']
fn native_update()
{
	if input.is_key_pressed(KeyCode.w)
	{
		log.info("W key held")
	}
}
