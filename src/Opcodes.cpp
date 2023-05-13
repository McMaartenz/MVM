#include "Opcodes.h"

namespace Opcodes {
Parser::Parser(uint8_t first_byte) {
	selection = (Selection)((first_byte & 0x0F) >> 1);
	opcode = (Opcode)(first_byte >> 4);
	relative_address = first_byte & 0b1;
}

Parser::~Parser() {
	// dtor
}
}
