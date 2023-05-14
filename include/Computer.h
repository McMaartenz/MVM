#ifndef COMPUTER_H
#define COMPUTER_H

#include "Memory.h"
#include "Disk.h"
#include "Opcodes.h"

class Computer {
  public:
	Memory* memory;
	Disk* disk_file;

	bool running;

	// Registers
	uint16_t IP;
	uint16_t SP;

	Computer(uint32_t memory_size, Disk* disk);
	virtual ~Computer();

	void boot();
	void tick();

  protected:

  private:
  	/* operand from memory/register/constant */
  	uint8_t get_operand_1(const Opcodes::Parser& parser);
  	uint8_t get_operand_2(const Opcodes::Parser& parser);

  	void set_operand_1(const Opcodes::Parser& parser, uint8_t value);
  	void set_operand_2(const Opcodes::Parser& parser, uint8_t value);
};

#endif // COMPUTER_H
