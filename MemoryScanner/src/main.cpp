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
		std::cout << "Enter the skin id you want to change: ";
		std::cin >> valueToScan;
		std::cout << "Enter the number you want to change: ";
		std::cin >> valueToChange;


		mem::ScanMemory(processHandle, valueToScan);
		mem::EditAllMemory(processHandle, valueToScan, valueToChange);

	} while (!GetAsyncKeyState(VK_END) & 1);



	return 0;
}
