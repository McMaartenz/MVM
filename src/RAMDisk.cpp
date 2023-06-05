#include "RAMDisk.h"

RAMDisk::RAMDisk(uint32_t disk_size) : Disk() {
	storage.resize(disk_size, 0);
}

RAMDisk::~RAMDisk() {
	//dtor
}

void RAMDisk::write(uint32_t offset, uint8_t value) {
	storage.at(offset) = value;
}

uint8_t RAMDisk::read(uint32_t offset) {
	return storage.at(offset);
}

void RAMDisk::write_many(uint32_t offset, const uint8_t* buffer, uint32_t count) {
	std::copy_n(buffer, count, storage.begin() + offset);
}

void RAMDisk::read_many(uint32_t offset, uint8_t* buffer, uint32_t count) {
	std::uninitialized_copy(std::begin(storage) + offset, std::begin(storage) + offset + count, buffer);
}
