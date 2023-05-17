#ifndef OPCODES_H
#define OPCODES_H

#include <cstdint>
#include <stdexcept>
#include <tuple>
#include <map>

enum Opcode {
	MOV,
	HLT,
	IN,
	OUT,
	JMP
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
	enum Type {
		Empty,
		Register,
		Address,
		Constant
	};

  public:
	Selection selection;
	Opcode opcode;

	uint8_t operand;
	uint8_t& address;

	bool relative_address;
	uint32_t length;

	uint8_t register_1;
	uint8_t register_2;

	Type operand_1;
	Type operand_2;

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
