using System;
using System.Net.Http;

namespace TestApp
{
    class Program
    {
        static void Main(string[] args)
        {
            TestClass test = new TestClass();
            test.IntArrayFn(new[] { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
            test.StringFn("Hello from C#");
            test.IntFn(1234);
            test.IntStringFn(2, "test");
            test.StructFn(new TestStruct { Int1 = 101, Int2 = 102, Int3 = 103 });
            test.StructFn(new OneFieldStruct { Int1 = 100 });
            TestClass.StaticIntArrayFn(new[] { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
            TestClass.StaticStringFn("Hello from C#");
            TestClass.StaticIntFn(1234);
            TestClass.StaticIntStringFn(2, "test");
            TestClass.StaticStructFn(new TestStruct { Int1 = 101, Int2 = 102, Int3 = 103 });
            TestClass.StaticStructFn(new OneFieldStruct { Int1 = 100 });
            "rua mua".Insert(2, "test");
            Console.ReadLine();
        }

    }

}
