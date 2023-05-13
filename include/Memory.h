#ifndef MEMORY_H
#define MEMORY_H

#include <cstdint>

class Memory {
  public:
	Memory(uint32_t memory_size = 512);
	virtual ~Memory();

	uint8_t* data;

  protected:

  private:
};

#endif // MEMORY_H
