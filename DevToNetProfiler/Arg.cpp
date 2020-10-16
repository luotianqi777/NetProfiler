#include "pch.h"
#include "Arg.h"

bool Arg::GetString(COR_PRF_FUNCTION_ARGUMENT_RANGE range,char** output)
{
    size_t size;
    return GetString(range, output, &size);
}

bool Arg::GetString(COR_PRF_FUNCTION_ARGUMENT_RANGE range,char** output, size_t* size)
{
    try
    {
        UINT_PTR valuePtr = range.startAddress;
        byte** ptr = (byte**)valuePtr;
        byte* strPtr = *ptr;
        strPtr += sizeof(int*);
        strPtr += 4;
        std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> codecvt;
        std::string str = codecvt.to_bytes((char16_t*)strPtr);
        if (size) {
            *size = str.length() + 1;
        }
        *output = new char[str.length()+1];
        strcpy_s(*output, str.length() + 1, str.c_str());
        return true;
    }
    catch (const std::exception&)
    {
        return false;
    }
}
