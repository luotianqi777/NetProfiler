using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TestApp
{
    struct TestStruct
    {
        public int Int1;
        public int Int2;
        public int Int3;
    }

    struct OneFieldStruct
    {
        public int Int1;
    }
    class TestClass
    {
        public void IntArrayFn(int[] intArray) { }
        public void StringFn(string str) { } 
        public void IntFn(int i1) { } 
        public void IntStringFn(int i1, string str) { } 
        public void StructFn(TestStruct t) { } 
        public void StructFn(OneFieldStruct t) { }
        public static void StaticIntArrayFn(int[] intArray) { }
        public static void StaticStringFn(string str) { } 
        public static void StaticIntFn(int i1) { } 
        public static void StaticIntStringFn(int i1, string str) { } 
        public static void StaticStructFn(TestStruct t) { } 
        public static void StaticStructFn(OneFieldStruct t) { }
    }

}
