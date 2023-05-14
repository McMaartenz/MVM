#ifndef OPCODES_H
#define OPCODES_H

#include <cstdint>
#include <stdexcept>

enum Opcode {
	MOV,
	HLT,
	IN,
	OUT
};

namespace Opcodes {
enum Selection {
	reg_reg,
	reg_im8,
	mem_reg,
	reg_mem,

	no_arguments,
	just_reg,
	just_mem,
	just_im8
};

class Parser {
  public:
	Selection selection;
	Opcode opcode;
	uint8_t operand;
	bool relative_address;
	uint32_t length;

	uint8_t register_1;
	uint8_t register_2;

	Parser(uint8_t first_byte);
	virtual ~Parser();

	void byte_2(uint8_t second_byte);
	void byte_3(uint8_t third_byte);

	static Selection get_selection(uint8_t first_byte);
	static uint32_t instruction_length(Selection selection);

  protected:
  private:
};
}

#endif // OPCODES_H
