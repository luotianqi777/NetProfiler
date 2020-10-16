#include "pch.h"
#include "Arg.h"
#include "Hooker.h"

Hooker::Hooker(char* _funcName)
{
    this->funcName = _funcName;
}

bool Hooker::AddHookFunctnion(const char* TargetFuncName, std::function<void(void)> argLogic)
{
    if (strcmp(TargetFuncName, this->funcName) == 0) {
        std::cout << TargetFuncName << " hooked\r\n";
        argLogic();
        std::cout << std::endl;
    }
    return false;
}

void Hooker::HookAllFuncations(char* funcName, COR_PRF_FUNCTION_ARGUMENT_INFO* argumentInfo)
{
    Hooker hooker(funcName);
    auto ranges = argumentInfo->ranges;

    // ²âÊÔÑùÀý
    hooker.AddHookFunctnion("IntFn", [ranges]() {
        int intArg;
        Arg::GetType<int>(ranges[1], &intArg);
        std::cout << intArg << "\r\n";
        });
    hooker.AddHookFunctnion("StringFn", [ranges]() {
        char* str;
        Arg::GetString(ranges[1], &str);
        std::cout << str << "\r\n";
        });
    hooker.AddHookFunctnion("StructFn", [ranges]() {
        UINT_PTR valuePtr = ranges[1].startAddress;
        int* ptr = (int*)valuePtr;
        std::cout << "arguments: Int1 = " << *ptr << ", Int2 = " << *(ptr + 1) << ", Int3 = " << *(ptr + 2) << "\r\n";
        });
    hooker.AddHookFunctnion("IntArrayFn", [ranges]() {
        int* array;
        size_t size;
        Arg::GetTypeArray<int>(ranges[1], &array, &size);
        for (size_t i = 0;i < size;i++) {
            std::cout << array[i] << " ";
        }
        std::cout << std::endl;
        });
    hooker.AddHookFunctnion("IntStringFn", [ranges]() {
        int intArg;
        char* str;
        Arg::GetType<int>(ranges[1], &intArg);
        Arg::GetString(ranges[2], &str);
        std::cout << intArg << " " << str << "\r\n";
        });
    hooker.AddHookFunctnion("StaticIntFn", [ranges]() {
        int intArg;
        Arg::GetType<int>(ranges[0], &intArg);
        std::cout << intArg << "\r\n";
        });
    hooker.AddHookFunctnion("StaticStringFn", [ranges]() {
        char* str;
        Arg::GetString(ranges[0], &str);
        std::cout << str << "\r\n";
        });
    hooker.AddHookFunctnion("StaticStructFn", [ranges]() {
        UINT_PTR valuePtr = ranges[0].startAddress;
        int* ptr = (int*)valuePtr;
        std::cout << "arguments: Int1 = " << *ptr << ", Int2 = " << *(ptr + 1) << ", Int3 = " << *(ptr + 2) << "\r\n";
        });
    hooker.AddHookFunctnion("StaticIntArrayFn", [ranges]() {
        int* array;
        size_t size;
        Arg::GetTypeArray<int>(ranges[0], &array, &size);
        for (size_t i = 0;i < size;i++) {
            std::cout << array[i] << " ";
        }
        std::cout << std::endl;
        });
    hooker.AddHookFunctnion("StaticIntStringFn", [ranges]() {
        int intArg;
        char* str;
        Arg::GetType<int>(ranges[0], &intArg);
        Arg::GetString(ranges[1], &str);
        std::cout << intArg << " " << str << "\r\n";
        });
    // String
    /*
    hooker.AddHookFunctnion("Insert", [ranges]() {
        int index;
        const char* str;
        Arg::GetType<int>(ranges[1], &index);
        Arg::GetString(ranges[2], &str);
        std::cout << index << " " << str << std::endl;
        });
	*/
}
