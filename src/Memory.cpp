#include "Memory.h"

Memory::Memory(uint32_t memory_size)
{
	data = new uint8_t[memory_size];
}

Memory::~Memory()
{
	delete[] data;
}
