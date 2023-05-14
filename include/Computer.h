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
	uint16_t IP; // IP, IPL(ow), IPH(igh)
	uint16_t SP; // SP, SPL, SPH
	uint16_t AX; // AX, AL, AH
	uint16_t BX; // BX, BL, BH
	uint8_t C;
	uint8_t D;
	uint8_t E;

	struct Flags { // 5/8 flags
		uint8_t ZF : 1;
		uint8_t CF : 1;
		uint8_t SF : 1;
		uint8_t OF : 1;
		uint8_t IF : 1;
		uint8_t Unused : 3;
	};

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
