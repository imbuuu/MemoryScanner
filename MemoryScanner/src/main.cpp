#include "pch.h"
#include "proc.h"
#include "common.h"
#include "mem.h"

int main()
{
	size_t valueToScan{};
	size_t valueToChange{};

	do
	{
		std::cout << "Enter the value you want to scan: ";
		std::cin >> valueToScan;
		std::cout << "Enter the new value: ";
		std::cin >> valueToChange;


		mem::ScanMemory(processHandle, valueToScan);
		mem::EditAllMemory(processHandle, valueToScan, valueToChange);

	} while (!GetAsyncKeyState(VK_END) & 1);



	return 0;
}
