namespace NeonManaged;

public class Class1
{
    internal static unsafe delegate*<void> InternalLogCall;

    public static void CallBackToInternal(float value)
    {
        unsafe { InternalLogCall(); }
    	Console.WriteLine(value);
    }
}
