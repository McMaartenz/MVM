#include "Opcodes.h"

namespace Opcodes {
Parser::Parser(uint8_t first_byte) : address(operand) {
	selection = get_selection(first_byte);
	opcode = (Opcode)(first_byte >> 4);
	relative_address = first_byte & 0b1;
	length = instruction_length(selection);

	std::map<Selection, std::tuple<Type,Type>> types_mapping = {
		{reg_reg, {Register, Register}},
		{reg_im8, {Register, Constant}},
		{mem_reg, {Address, Register}},
		{reg_mem, {Register, Address}},
		{no_arguments, {Empty, Empty}},
		{just_reg, {Register, Empty}},
		{just_mem, {Address, Empty}},
		{just_im8, {Constant, Empty}}
	};

	auto types = types_mapping[selection];
	operand_1 = std::get<0>(types);
	operand_2 = std::get<1>(types);
}

Parser::~Parser() {
	// dtor
}

void Parser::byte_2(uint8_t second_byte) {
	switch (selection) {
	case reg_reg:
	case just_reg:
	case reg_mem:
	case mem_reg:
	case reg_im8:
		register_1 = (second_byte & 0b1111'0000) >> 4;
		register_2 =  second_byte & 0b0000'1111;
		break;

	default:
		operand = second_byte;
	}
}

void Parser::byte_3(uint8_t third_byte) {
	if (length < 3) {
		throw std::logic_error("No third byte when instruction length is less than 3");
	}

	operand = third_byte;
}

Selection Parser::get_selection(uint8_t first_byte) {
	return (Selection)((first_byte & 0b0000'1110) >> 1); // OOOO SSSR Opcode Selection Relative
}

uint32_t Parser::instruction_length(Opcodes::Selection selection) {
	switch (selection) {
	case no_arguments:
		return 1;

	case reg_reg:
	case just_im8:
	case just_reg:
	case just_mem:
		return 2;

	case reg_mem:
	case mem_reg:
	case reg_im8:
		return 3;
	}

	throw std::invalid_argument("No such opcode selection");
}
}
