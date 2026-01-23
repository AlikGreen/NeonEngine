import std.stdio;
import std.format;

class Log
{
    public static void info(T...)(string fmt, T args)
    {
        writefln(fmt.format(args));
    }
}
