#pragma once
class Hooker
{
private:
    char* funcName;
public:
    Hooker(char* _funcName);
    bool AddHookFunctnion(const char* TargetFuncName, std::function<void(void)> argLogic);
    static void HookAllFuncations(char* funcName, COR_PRF_FUNCTION_ARGUMENT_INFO* argumentInfo);
};

