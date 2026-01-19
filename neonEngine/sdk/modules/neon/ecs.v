module neon

// struct Position {
// 	mut:
// 	x f32
// 	y f32
// }
//
// struct Velocity {
// 	mut:
// 	vx f32
// 	vy f32
// }
//
// struct View2[T1, T2] {
// 	world voidptr
// }
//
// struct View2Iter[T1, T2] {
// 	world voidptr
// 	mut:
// 	cursor int
// }
//
// fn (v View2[T1, T2]) iter() View2Iter[T1, T2]
// {
// 	return View2Iter[T1, T2]
// 	{
// 		world: v.world
// 		cursor: 0
// 	}
// }
//
// fn (mut it View2Iter[T1, T2]) next() ?View2Result[T1, T2] {
//
// }