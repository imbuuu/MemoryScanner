#pragma once

#include "pch.h"

namespace proc
{
	DWORD GetProcId(const wchar_t* modName);

	uintptr_t GetModBaseAddr(DWORD procId, const wchar_t* modName);

	uintptr_t FindDMAAddy(HANDLE hProcess, uintptr_t ptr, std::vector<unsigned int> offsets);
}

