module neon

#include <stdio.h>
fn C.printf(format &char, ...voidptr) int

struct Log {

}

pub fn (_ Log) info(text string)
{
	unsafe
	{
		C.printf(c"[V script][info] %s\n", text.str)
	}
}