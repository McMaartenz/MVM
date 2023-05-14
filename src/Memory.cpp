#include "Memory.h"

Memory::Memory(uint32_t memory_size) {
	data = new uint8_t[memory_size];
}

Memory::~Memory() {
	delete[] data;
}

uint8_t Memory::get(uint32_t address) {
	// TODO: Apply MMU logic
	return data[address];
}

void Memory::set(uint32_t address, uint8_t value) {
	// TODO: Apply MMU logic
	data[address] = value;
}

void Memory::write_buffer(uint32_t address, uint8_t* buffer, uint32_t count) {
	std::memcpy(data + address, buffer, count);
}
