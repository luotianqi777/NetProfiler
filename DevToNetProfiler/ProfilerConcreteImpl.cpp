#include "pch.h"
#include "ProfilerConcreteImpl.h"
#include "Naked32Bit.h"
#include "Arg.h"
#include "Hooker.h"

#include <locale>
#include <codecvt>
#include <cuchar>
CComQIPtr<ICorProfilerInfo8> iCorProfilerInfo;
Utils* utils;

HRESULT __stdcall DoStackSnapshotCallback(
  FunctionID funcId,
  UINT_PTR ip,
  COR_PRF_FRAME_INFO frameInfo,
  ULONG32 contextSize,
  BYTE context[],
  void* clientData
);

struct SnapshotClientData {
  Utils* pUtils;
  char* stacktrace;
};

ProfilerConcreteImpl::ProfilerConcreteImpl() {
  this->ActivateCallbacks = true;
  this->PHashMap = NULL;
}

HRESULT ProfilerConcreteImpl::FinalConstruct()
{
  return S_OK;
}
void ProfilerConcreteImpl::FinalRelease() {
}

const int mapSize = 10000;

HRESULT __stdcall ProfilerConcreteImpl::Initialize(IUnknown* pICorProfilerInfoUnk)
{
    pICorProfilerInfoUnk->QueryInterface(IID_ICorProfilerInfo2, (LPVOID*)&iCorProfilerInfo);
    iCorProfilerInfo->SetEventMask(COR_PRF_MONITOR_EXCEPTIONS | COR_PRF_MONITOR_OBJECT_ALLOCATED
        | COR_PRF_ENABLE_OBJECT_ALLOCATED | COR_PRF_ENABLE_STACK_SNAPSHOT
        | COR_PRF_MONITOR_ENTERLEAVE | COR_PRF_ENABLE_FUNCTION_ARGS);

    iCorProfilerInfo->SetEnterLeaveFunctionHooks2((FunctionEnter2*)&FnEnterCallback, (FunctionLeave2*)FnLeaveCallback, (FunctionTailcall2*)FnTailcallCallback);

    this->PHashMap = new int[mapSize];
    memset(this->PHashMap, 0, mapSize);
    InitEnterLeaveCallbacks(&this->ActivateCallbacks, this->PHashMap, mapSize);
    std::cout << "profiler start!\n";
    utils = new Utils(iCorProfilerInfo);
    return S_OK;
}

HRESULT __stdcall ProfilerConcreteImpl::ExceptionThrown(ObjectID thrownObjectID)
{
  char* className = new char[100];
  utils->GetClassNameByObjectId(thrownObjectID, className, 100);
  //cout << "\t\nfrom profiler: exception thrown: " << className << "\r\n";
  delete[] className;
  return S_OK;
}

HRESULT __stdcall ProfilerConcreteImpl::ObjectAllocated(ObjectID objectID, ClassID classID)
{
  char* className = new char[1000];

  if (utils->GetClassNameByClassId(classID, className, 1000)) {
    // std::cout << "\t\nfrom profiler: class allocated: " << className << "\r\n";

    if (strcmp(className, "TestApp.CatBowlEmptyException") == 0) {
      char* stack = new char[1000];
      memset(stack, 0, 1000);
      SnapshotClientData clientData;
      clientData.pUtils = utils;
      clientData.stacktrace = stack;
      iCorProfilerInfo->DoStackSnapshot(NULL, &DoStackSnapshotCallback, COR_PRF_SNAPSHOT_DEFAULT, &clientData, 0, 0);
      std::cout << "stack:\r\n" << stack;
      delete[] stack;
    }   
  }

  delete[] className;
  return S_OK;
}

HRESULT __stdcall DoStackSnapshotCallback(
  FunctionID funcId,
  UINT_PTR ip,
  COR_PRF_FRAME_INFO frameInfo,
  ULONG32 contextSize,
  BYTE context[],
  void* clientData
) {
  if (funcId == 0) {
    return S_OK;
  }

  SnapshotClientData* snapshotClientData = (SnapshotClientData*)clientData;
  char* output = snapshotClientData->stacktrace + strlen(snapshotClientData->stacktrace);
  output[0] = '\r';
  output[1] = '\n';
  output += 2;
  snapshotClientData->pUtils->GetFunctionNameById(funcId, output, 1000);

  return S_OK;
}

extern "C" void _stdcall StackOverflowDetected(FunctionID funcId, int count) {
  std::cout << "stackoverflow: " << funcId << ", count: " << count;
}

extern "C" void _stdcall EnterCpp(
    FunctionID funcId,
    COR_PRF_FUNCTION_ARGUMENT_INFO * argumentInfo) {

    char* fnName = new char[100];
    utils->GetFunctionNameById(funcId, fnName, 100);
    Hooker::HookAllFuncations(fnName, argumentInfo);

    delete[] fnName;
}

