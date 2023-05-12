#include "Disk.h"

Disk::Disk(std::string path)
{
	if (!std::filesystem::exists(path)) {
		throw std::runtime_error("Disk file does not exist");
	}

	stream.open(path, std::ios::in | std::ios::out | std::ios::binary);
}

Disk::~Disk()
{
	//dtor
}

void Disk::write(uint32_t offset, uint8_t value) {
	stream.seekp(offset, std::ios::beg);
	stream << value;
}

uint8_t Disk::read(uint32_t offset) {
	stream.seekg(offset, std::ios::beg);

	uint8_t read;
	stream >> read;
	return read;
}

void Disk::writeMany(uint32_t offset, const uint8_t* buffer, uint32_t count) {
	stream.seekp(offset, std::ios::beg);
	stream.write((const char*)buffer, count);
}

void Disk::readMany(uint32_t offset, uint8_t* buffer, uint32_t count) {
	stream.seekg(offset, std::ios::beg);
	stream.read((char*)buffer, count);
}
