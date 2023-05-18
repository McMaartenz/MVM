#include "Computer.h"

Computer::Computer(uint32_t memory_size, Disk* disk) : disk_file(disk), IO(256) {
	memory = new Memory(memory_size);
	for (int i = 0; i < 256; i++) {
		IO[i] = Port();
	}
}

Computer::~Computer() {
	//dtor
}

// Copy 0x000 - 0x200 (512) from disk file to RAM, jump to [0x000]
void Computer::boot() {
	IP = 0x0000;
	SP = 0x02FF; // Give 0xFF addresses of RAM for stack until the OS initializes this

	running = true;

	uint8_t buffer[512] {0};
	disk_file->read_many(0, buffer, 0x200);
	memory->write_buffer(0, buffer, 0x200);
}

void Computer::tick() {
	uint8_t byte_1,
			byte_2 = 0,
			byte_3 = 0;

	Opcodes::Parser parser;

	try {
		byte_1 = memory->get(IP); // Opcode and options
		parser.from(byte_1);

		if (parser.length > 1) {
			byte_2 = memory->get(IP + 1); // Registers, constant, or empty
			parser.byte_2(byte_2);

			if (parser.length > 2) {
				byte_3 = memory->get(IP + 2); // Constant or empty
				parser.byte_3(byte_3);
			}
		}
	} catch(const std::out_of_range& e) {
		// TODO: Throw BUS error interrupt
		std::cout << "[i] BUS error thrown at IP=" << std::hex << IP << std::endl;
		running = false;
		return;
	}

	bool branched = false;

	switch (parser.opcode) {
	case MOV: {
		set_operand_1(parser, get_operand_2(parser));
		break;
	}

	case OUT: {
		IO[get_operand_2(parser)].out(get_operand_1(parser));
		break;
	}

	case IN: {
		set_operand_1(parser, IO[get_operand_2(parser)].in());
		break;
	}

	case HLT: {
		running = false;
		return;
	}

	case JNZ: {
		if (ZF) {
			break; // It is zero
		}

		uint16_t jump_address = 0;
		switch (parser.selection) {
		case Opcodes::reg_reg:
		case Opcodes::reg_im8:
		case Opcodes::mem_reg:
		case Opcodes::reg_mem: {
			jump_address |= get_operand_2(parser)
							| (get_operand_1(parser) << 8);
			break;
		}

		case Opcodes::just_mem:
		case Opcodes::just_reg:
		case Opcodes::just_im8: {
			jump_address |= get_operand_1(parser);
			break;
		}

		default: {
			std::cout << "[!] Illegal instruction IP=" << std::hex << IP << std::endl;
			return; // TODO: illegal instruction interrupt
		}
		}

		IP = jump_address;
		branched = true;
		break;
	}

	case ADD: {
		uint16_t result = get_operand_1(parser) + get_operand_2(parser);
		set_operand_1(parser, (uint8_t)result);
		set_flags(result);
		break;
	}

	case SUB: {
		uint16_t result = get_operand_1(parser) - get_operand_2(parser);
		set_operand_1(parser, (uint8_t)result);
		set_flags(result);
		break;
	}

	default: {
		std::cout << "[!] Unknown instruction IP=" << std::hex << IP << std::endl;
		break;
	}
	}

	if (!branched) {
		IP += parser.length;
	}
}

// The below all can be done more elegantly
uint8_t Computer::get_operand_1(const Opcodes::Parser& parser) {
	using namespace Opcodes;

	switch (parser.operand_1) {
	case Parser::Register:
		return get_register(parser.register_1);

	case Parser::Address:
		return memory->get(parser.address);

	case Parser::Constant:
		return parser.operand;

	case Parser::Empty:
		throw std::logic_error("Cannot fetch empty operand"); // TODO: throw interrupt

	default:
		throw std::logic_error("Unknown type");
	}
}

uint8_t Computer::get_operand_2(const Opcodes::Parser& parser) {
	using namespace Opcodes;

	switch (parser.operand_2) {
	case Parser::Register:
		return get_register(parser.register_2);

	case Parser::Address:
		return memory->get(parser.address);

	case Parser::Constant:
		return parser.operand;

	case Parser::Empty:
		throw std::logic_error("Cannot fetch empty operand"); // TODO: throw interrupt

	default:
		throw std::logic_error("Unknown type");
	}
}

void Computer::set_operand_1(const Opcodes::Parser& parser, uint8_t value) {
	using namespace Opcodes;

	switch (parser.operand_1) {
	case Parser::Register:
		get_register(parser.register_1) = value;
		break;

	case Parser::Address:
		memory->set(parser.address, value);
		break;

	case Parser::Constant:
		throw std::logic_error("Cannot write to a constant literal"); // TODO: throw interrupt

	case Parser::Empty:
		throw std::logic_error("Cannot write to an empty operand");

	default:
		throw std::logic_error("Unknown type");
	}
}

void Computer::set_operand_2(const Opcodes::Parser& parser, uint8_t value) {
	using namespace Opcodes;

	switch (parser.operand_2) {
	case Parser::Register:
		get_register(parser.register_2) = value;
		break;

	case Parser::Address:
		memory->set(parser.address, value);
		break;

	case Parser::Constant:
		throw std::logic_error("Cannot write to a constant literal"); // TODO: throw interrupt

	case Parser::Empty:
		throw std::logic_error("Cannot write to an empty operand");

	default:
		throw std::logic_error("Unknown type");
	}
}

uint8_t& Computer::get_register(uint8_t register_number) {
	std::map<uint8_t, uint8_t*> register_mapping = {
		{0b0000, &IPL},
		{0b0001, &IPH},
		{0b0010, &SPL},
		{0b0011, &SPH},
		{0b0100, &AL},
		{0b0101, &AH},
		{0b0110, &BL},
		{0b0111, &BH},
		{0b1000, &CL},
		{0b1001, &CH},
		{0b1010, &DL},
		{0b1011, &DH},
		{0b1100, &EL},
		{0b1101, &EH},
		{0b1110, &Flags} // TODO: 0b1111 not implemented deliberately
	};

	return *register_mapping[register_number];
}

void Computer::set_flags(uint16_t value) {
	ZF = value == 0;
	CF = value > UINT8_MAX;
	SF = (value & 0b1000'0000) > 0;
}
