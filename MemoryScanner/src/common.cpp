#include "pch.h"
#include "proc.h"
#include "common.h"

DWORD procId = proc::GetProcId(L"HD-Player.exe");
HANDLE processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procId);
uintptr_t moduleBase = proc::GetModBaseAddr(procId, L"HD-Player.exe");

