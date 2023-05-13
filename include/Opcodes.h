#ifndef OPCODES_H
#define OPCODES_H

#include <cstdint>

enum Opcode {
	MOV,
	HLT
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
	bool relative_address;

	Parser(uint8_t first_byte);
	virtual ~Parser();

  protected:
  private:
};
}

#endif // OPCODES_H
