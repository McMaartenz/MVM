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
	union { uint16_t IP; struct { uint8_t IPL; uint8_t IPH; }; }; // IPL(ow), IPH(igh)
	union { uint16_t SP; struct { uint8_t SPL; uint8_t SPH; }; }; // SPL, SPH
	union { uint16_t AX; struct { uint8_t AL; uint8_t AH; }; }; // AL, AH
	union { uint16_t BX; struct { uint8_t BL; uint8_t BH; }; }; // BL, BH
	union { uint16_t CX; struct { uint8_t CL; uint8_t CH; }; }; // CL, CH
	union { uint16_t DX; struct { uint8_t DL; uint8_t DH; }; }; // DL, DH
	union { uint16_t EX; struct { uint8_t EL; uint8_t EH; }; }; // EL, EH

	union {
		uint8_t Flags;
		struct { // 5/8 flags
			uint8_t ZF : 1;
			uint8_t CF : 1;
			uint8_t SF : 1;
			uint8_t OF : 1;
			uint8_t IF : 1;
			uint8_t Unused : 3;
		};
	};

	// TODO: Flag for 16th

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

  	uint8_t& get_register(uint8_t register_number);
};

#endif // COMPUTER_H
