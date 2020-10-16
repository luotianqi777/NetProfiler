#pragma once
#include<codecvt>
#include<iostream>

class Arg
{
public:
    template<typename T>
    static bool GetType(COR_PRF_FUNCTION_ARGUMENT_RANGE range, T* output);
    template<typename T>
    static bool GetTypeArray(COR_PRF_FUNCTION_ARGUMENT_RANGE range, T** output, size_t* size);
    static bool GetString(COR_PRF_FUNCTION_ARGUMENT_RANGE range,char** output);
    static bool GetString(COR_PRF_FUNCTION_ARGUMENT_RANGE range,char** output, size_t* size);
};

template<typename T>
inline bool Arg::GetType(COR_PRF_FUNCTION_ARGUMENT_RANGE range, T* output)
{
    try
    {
        UINT_PTR valuePtr = range.startAddress;
        *output = *(T*)valuePtr;
        return true;
    }
    catch (const std::exception&)
    {
        return false;
    }
	return false;
}

template<typename T>
inline bool Arg::GetTypeArray(COR_PRF_FUNCTION_ARGUMENT_RANGE range, T** output, size_t* size)
{
    try
    {
        UINT_PTR valuePtr = range.startAddress;
        T** ptr = (T**)valuePtr;
        T* arrayPtr = *ptr;
        arrayPtr = arrayPtr + sizeof(T*) / sizeof(T); //skip object header of array
        size_t arrayLength = *(size_t*)arrayPtr;
        *size = arrayLength;
        arrayPtr += sizeof(T*) / sizeof(T);
        *output = arrayPtr;
        return true;
    }
    catch (const std::exception&)
    {
        return false;
    }
}
