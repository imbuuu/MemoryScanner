#pragma once
#include "pch.h"


namespace mem
{
	void ScanMemory(HANDLE processHandle, int valueToScan);

	void EditAllMemory(HANDLE processHandle, int valueToEdit, int newValue);

	void MEM_MAPPED_EditMemory(HANDLE processHandle, uintptr_t moduleBase, int valueToEdit, int newValue);

	void EditImageMemory(HANDLE processHandle, uintptr_t moduleBase, int valueToEdit, int newValue);

	void EditPrivateMemory(HANDLE processHandle, uintptr_t moduleBase, int valueToEdit, int newValue);

	void EditFreeMemory(HANDLE processHandle, int valueToEdit, int newValue);
}