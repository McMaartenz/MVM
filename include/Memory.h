#ifndef MEMORY_H
#define MEMORY_H

#include <cstdint>
#include <cstring>

class Memory {
  public:
	Memory(uint32_t memory_size = 512);
	virtual ~Memory();

	uint8_t get(uint32_t address);
	void set(uint32_t address, uint8_t value);
	void write_buffer(uint32_t address, uint8_t* buffer, uint32_t count);

  protected:

  private:
	uint8_t* data;

};

#endif // MEMORY_H
