#include "pch.h"
#include "Arg.h"

bool Arg::GetString(COR_PRF_FUNCTION_ARGUMENT_RANGE range, std::string* output)
{
    size_t size;
    return GetString(range, output, &size);
}

bool Arg::GetString(COR_PRF_FUNCTION_ARGUMENT_RANGE range, std::string* output, size_t* size)
{
    try
    {
        UINT_PTR valuePtr = range.startAddress;
        byte** ptr = (byte**)valuePtr;
        byte* strPtr = *ptr;
        strPtr = strPtr + sizeof(int*);
        if (size) {
            *size = *(size_t*)strPtr;
        }
        strPtr += 4;
        char* dest = new char[100];
        std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> codecvt;
        *output = codecvt.to_bytes((char16_t*)strPtr).c_str();
        return true;
    }
    catch (const std::exception&)
    {
        return false;
    }
}
