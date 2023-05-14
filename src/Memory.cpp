#include "Memory.h"

Memory::Memory(uint32_t memory_size) {
	data.reserve(memory_size);
}

Memory::~Memory() {
	// dtor
}

uint8_t Memory::get(uint32_t address) {
	// TODO: Apply MMU logic
	return data[address];
}

void Memory::set(uint32_t address, uint8_t value) {
	// TODO: Apply MMU logic
	data[address] = value;
}

void Memory::write_buffer(uint32_t address, const uint8_t* buffer, uint32_t count) {
	// TODO: Apply MMU logic (How would this be done? e.g. in terms of optimization to still get great throughput)
	std::copy_n(buffer, count, data.begin() + address);
}
