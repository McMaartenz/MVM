#ifndef RAMDISK_H
#define RAMDISK_H

#include <Disk.h>

class RAMDisk : public Disk
{
public:
	RAMDisk(uint32_t disk_size);
	virtual ~RAMDisk();

	void write(uint32_t offset, uint8_t value);
	uint8_t read(uint32_t offset);

	void write_many(uint32_t offset, const uint8_t* buffer, uint32_t count);
	void read_many(uint32_t offset, uint8_t* buffer, uint32_t count);

protected:
	std::vector<uint8_t> storage;
private:
};

#endif // RAMDISK_H
