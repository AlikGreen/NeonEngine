module neon

struct Input {

}

pub fn (_ Input) is_key_held(k KeyCode) bool
{
	return g_cb_struct.is_key_held(int(k))
}

pub fn (_ Input) is_key_pressed(k KeyCode) bool
{
	return g_cb_struct.is_key_pressed(int(k))
}

pub fn (_ Input) is_key_released(k KeyCode) bool
{
	return g_cb_struct.is_key_released(int(k))
}