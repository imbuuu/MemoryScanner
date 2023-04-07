#include "pch.h"
#include "mem.h"
#include "proc.h"

void mem::ScanMemory(HANDLE processHandle, int valueToScan)
{

	SYSTEM_INFO systemInfo;
	GetSystemInfo(&systemInfo);

	uintptr_t address = 0;
	MEMORY_BASIC_INFORMATION memoryInfo;
	while (VirtualQueryEx(processHandle, (LPVOID)address, &memoryInfo, sizeof(memoryInfo))) {
		if (memoryInfo.State == MEM_COMMIT) {
			BYTE* buffer = new BYTE[memoryInfo.RegionSize];
			SIZE_T bytesRead;

			if (ReadProcessMemory(processHandle, memoryInfo.BaseAddress, buffer, memoryInfo.RegionSize, &bytesRead) && bytesRead > 0) {
				for (uintptr_t i = 0; i < bytesRead; i += sizeof(int)) {
					int* currentValue = (int*)(buffer + i);
					if (*currentValue == valueToScan) {
						std::cout << "Address: " << std::hex << (uintptr_t)(memoryInfo.BaseAddress) + i << std::endl;
					}
				}
			}

			delete[] buffer;
		}

		address += memoryInfo.RegionSize;
	}
}


void mem::EditAllMemory(HANDLE processHandle, int valueToEdit, int newValue)
{
	SYSTEM_INFO systemInfo;
	GetSystemInfo(&systemInfo);

	uintptr_t address = (uintptr_t)systemInfo.lpMinimumApplicationAddress;
	MEMORY_BASIC_INFORMATION memoryInfo;

	while (address < (uintptr_t)systemInfo.lpMaximumApplicationAddress) {
		if (VirtualQueryEx(processHandle, (LPCVOID)address, &memoryInfo, sizeof(memoryInfo)) == sizeof(memoryInfo)) {
			if (memoryInfo.State == MEM_COMMIT && (memoryInfo.Protect & (PAGE_READWRITE | PAGE_WRITECOPY | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY))) {
				BYTE* buffer = new BYTE[memoryInfo.RegionSize];
				SIZE_T bytesRead;

				if (ReadProcessMemory(processHandle, memoryInfo.BaseAddress, buffer, memoryInfo.RegionSize, &bytesRead) && bytesRead > 0) {
					for (uintptr_t i = 0; i < bytesRead; i += sizeof(int)) {
						int* currentValue = (int*)(buffer + i);
						if (*currentValue == valueToEdit) {
							// Write new value to memory
							uintptr_t addressToEdit = (uintptr_t)(memoryInfo.BaseAddress) + i;
							DWORD oldProtect;
							VirtualProtectEx(processHandle, (LPVOID)addressToEdit, sizeof(int), PAGE_EXECUTE_READWRITE, &oldProtect);
							WriteProcessMemory(processHandle, (LPVOID)addressToEdit, &newValue, sizeof(newValue), nullptr);
							VirtualProtectEx(processHandle, (LPVOID)addressToEdit, sizeof(int), oldProtect, &oldProtect);
						}
					}
				}

				delete[] buffer;
			}
		}

		address += memoryInfo.RegionSize;
	}
}


void mem::MEM_MAPPED_EditMemory(HANDLE processHandle, uintptr_t moduleBase, int valueToEdit, int newValue)
{
	SYSTEM_INFO systemInfo;
	GetSystemInfo(&systemInfo);

	MEMORY_BASIC_INFORMATION memoryInfo;
	uintptr_t address = moduleBase;

	while (address < (uintptr_t)systemInfo.lpMaximumApplicationAddress) {
		if (VirtualQueryEx(processHandle, (LPVOID)address, &memoryInfo, sizeof(memoryInfo)) == sizeof(memoryInfo)) {
			if (memoryInfo.State == MEM_COMMIT && memoryInfo.Type == MEM_MAPPED && (memoryInfo.Protect & (PAGE_EXECUTE_READWRITE | PAGE_READWRITE))) {
				BYTE* buffer = new BYTE[memoryInfo.RegionSize];
				SIZE_T bytesRead;

				if (ReadProcessMemory(processHandle, memoryInfo.BaseAddress, buffer, memoryInfo.RegionSize, &bytesRead) && bytesRead > 0) {
					for (uintptr_t i = 0; i < bytesRead; i += sizeof(int)) {
						int* currentValue = (int*)(buffer + i);
						if (*currentValue == valueToEdit) {
							// Write new value to memory
							uintptr_t addressToEdit = (uintptr_t)(memoryInfo.BaseAddress) + i;
							DWORD oldProtect;
							VirtualProtectEx(processHandle, (LPVOID)addressToEdit, sizeof(newValue), PAGE_READWRITE, &oldProtect);
							WriteProcessMemory(processHandle, (LPVOID)addressToEdit, &newValue, sizeof(newValue), nullptr);
							VirtualProtectEx(processHandle, (LPVOID)addressToEdit, sizeof(newValue), oldProtect, &oldProtect);
						}
					}
				}

				delete[] buffer;
			}
		}

		address += memoryInfo.RegionSize;
	}
}


void mem::EditPrivateMemory(HANDLE processHandle, uintptr_t moduleBase, int valueToEdit, int newValue)
{
	SYSTEM_INFO systemInfo;
	GetSystemInfo(&systemInfo);

	MEMORY_BASIC_INFORMATION memoryInfo;
	uintptr_t address = moduleBase;

	while (address < (uintptr_t)systemInfo.lpMaximumApplicationAddress) {
		if (VirtualQueryEx(processHandle, (LPVOID)address, &memoryInfo, sizeof(memoryInfo)) == sizeof(memoryInfo)) {
			if (memoryInfo.State == MEM_COMMIT && memoryInfo.Type == MEM_PRIVATE && (memoryInfo.Protect & (PAGE_EXECUTE_READWRITE | PAGE_READWRITE))) {
				BYTE* buffer = new BYTE[memoryInfo.RegionSize];
				SIZE_T bytesRead;

				if (ReadProcessMemory(processHandle, memoryInfo.BaseAddress, buffer, memoryInfo.RegionSize, &bytesRead) && bytesRead > 0) {
					for (uintptr_t i = 0; i < bytesRead; i += sizeof(int)) {
						int* currentValue = (int*)(buffer + i);
						if (*currentValue == valueToEdit) {
							// Write new value to memory
							uintptr_t addressToEdit = (uintptr_t)(memoryInfo.BaseAddress) + i;
							DWORD oldProtect;
							VirtualProtectEx(processHandle, (LPVOID)addressToEdit, sizeof(int), PAGE_EXECUTE_READWRITE, &oldProtect);
							WriteProcessMemory(processHandle, (LPVOID)addressToEdit, &newValue, sizeof(newValue), nullptr);
							VirtualProtectEx(processHandle, (LPVOID)addressToEdit, sizeof(int), oldProtect, &oldProtect);
						}
					}
				}

				delete[] buffer;
			}
		}

		address += memoryInfo.RegionSize;
	}
}

void mem::EditImageMemory(HANDLE processHandle, uintptr_t moduleBase, int valueToEdit, int newValue)
{
	SYSTEM_INFO systemInfo;
	GetSystemInfo(&systemInfo);

	MEMORY_BASIC_INFORMATION memoryInfo;
	uintptr_t address = moduleBase;

	while (address < (uintptr_t)systemInfo.lpMaximumApplicationAddress) {
		if (VirtualQueryEx(processHandle, (LPVOID)address, &memoryInfo, sizeof(memoryInfo)) == sizeof(memoryInfo)) {
			if (memoryInfo.State == MEM_COMMIT && memoryInfo.Type == MEM_IMAGE && (memoryInfo.Protect & (PAGE_EXECUTE_READWRITE | PAGE_READWRITE))) {
				BYTE* buffer = new BYTE[memoryInfo.RegionSize];
				SIZE_T bytesRead;

				if (ReadProcessMemory(processHandle, memoryInfo.BaseAddress, buffer, memoryInfo.RegionSize, &bytesRead) && bytesRead > 0) {
					for (uintptr_t i = 0; i < bytesRead; i += sizeof(int)) {
						int* currentValue = (int*)(buffer + i);
						if (*currentValue == valueToEdit) {
							// Write new value to memory
							uintptr_t addressToEdit = (uintptr_t)(memoryInfo.BaseAddress) + i;
							DWORD oldProtect;
							VirtualProtectEx(processHandle, (LPVOID)addressToEdit, sizeof(int), PAGE_EXECUTE_READWRITE, &oldProtect);
							WriteProcessMemory(processHandle, (LPVOID)addressToEdit, &newValue, sizeof(newValue), nullptr);
							VirtualProtectEx(processHandle, (LPVOID)addressToEdit, sizeof(int), oldProtect, &oldProtect);
						}
					}
				}

				delete[] buffer;
			}
		}

		address += memoryInfo.RegionSize;
	}
}

void mem::EditFreeMemory(HANDLE processHandle, int valueToEdit, int newValue)
{
	SYSTEM_INFO systemInfo;
	GetSystemInfo(&systemInfo);

	MEMORY_BASIC_INFORMATION memoryInfo;
	uintptr_t address = (uintptr_t)systemInfo.lpMinimumApplicationAddress;

	while (address < (uintptr_t)systemInfo.lpMaximumApplicationAddress) {
		if (VirtualQueryEx(processHandle, (LPVOID)address, &memoryInfo, sizeof(memoryInfo)) == sizeof(memoryInfo)) {
			if (memoryInfo.State == MEM_FREE) {
				uintptr_t regionStart = (uintptr_t)memoryInfo.BaseAddress;
				uintptr_t regionEnd = regionStart + memoryInfo.RegionSize;

				// Reserve the memory
				LPVOID region = VirtualAllocEx(processHandle, (LPVOID)regionStart, memoryInfo.RegionSize, MEM_COMMIT, PAGE_READWRITE);
				if (region == NULL) {
					continue;
				}
				else {
					// Assign the returned address to the region variable
					region = (LPVOID)regionStart;
				}

				// Fill the memory with the new value
				int* buffer = new int[memoryInfo.RegionSize / sizeof(int)];
				std::fill(buffer, buffer + (memoryInfo.RegionSize / sizeof(int)), newValue);

				SIZE_T bytesWritten;
				if (WriteProcessMemory(processHandle, region, buffer, memoryInfo.RegionSize, &bytesWritten)) {
					// Release the memory
					VirtualFreeEx(processHandle, region, 0, MEM_RELEASE);
				}

				delete[] buffer;
			}
		}

		address = (uintptr_t)memoryInfo.BaseAddress + memoryInfo.RegionSize;
	}
}




