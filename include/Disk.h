#ifndef DISK_H
#define DISK_H

#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>

#include <stdexcept>

class Disk {
  public:
	Disk(std::string path);
	virtual ~Disk();

	void write(uint32_t offset, uint8_t value);
	uint8_t read(uint32_t offset);

	void write_many(uint32_t offset, const uint8_t* buffer, uint32_t count);
	void read_many(uint32_t offset, uint8_t* buffer, uint32_t count);

  protected:

  private:
	std::fstream stream;
};

#endif // DISK_H
