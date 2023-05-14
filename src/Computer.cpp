#include "Computer.h"

Computer::Computer(uint32_t memory_size, Disk* disk) : disk_file(disk) {
	memory = new Memory(memory_size);
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

	Opcodes::Parser* parser = nullptr;

	try {
		byte_1 = memory->get(IP);     // Opcode and options
		parser = new Opcodes::Parser(byte_1);

		if (parser->length > 1) {
			byte_2 = memory->get(IP + 1); // Registers, constant, or empty
			parser->byte_2(byte_2);

			if (parser->length > 2) {
				byte_3 = memory->get(IP + 2); // Constant or empty
				parser->byte_3(byte_3);
			}
		}
	} catch(const std::out_of_range& e) {
		// TODO: Throw BUS error interrupt
		std::cout << "[i] BUS error thrown at IP=" << std::hex << IP << std::endl;
		running = false;
		return;
	}

	switch (parser->opcode) {
	case MOV: {
		std::cout << "MOV!\n";
		break;
	}

	case OUT: {
		std::cout << "OUT\n";
		break;
	}

	case IN: {
		std::cout << "IN\n";
		break;
	}

	case HLT: {
		running = false;
		return;
	}
	}

	// Jump should skip this!
	IP += parser->length;
}

uint8_t Computer::get_operand_1(const Opcodes::Parser& parser) {
	using namespace Opcodes;

	switch (parser.operand_1) {
	case Parser::Register:
		// dont have em
		throw std::logic_error("Not implemented");

	case Parser::Address:
		return memory->get(parser.operand);

	case Parser::Constant:
		return parser.operand;

	case Parser::Empty:
		throw std::logic_error("Cannot fetch empty operand");

	default:
		throw std::logic_error("Unknown type");
	}
}

uint8_t Computer::get_operand_2(const Opcodes::Parser& parser) {
	using namespace Opcodes;

	switch (parser.operand_2) {
	case Parser::Register:
		// dont have em
		throw std::logic_error("Not implemented");

	case Parser::Address:
		return memory->get(parser.operand);

	case Parser::Constant:
		return parser.operand;

	case Parser::Empty:
		throw std::logic_error("Cannot fetch empty operand");

	default:
		throw std::logic_error("Unknown type");
	}
}

void Computer::set_operand_1(const Opcodes::Parser& parser, uint8_t value) {
	using namespace Opcodes;

	switch (parser.operand_1) {
	case Parser::Register:
		// dont have em
		throw std::logic_error("Not implemented");

	case Parser::Address:
		return memory->set(parser.operand, value);

	case Parser::Constant:
		throw std::logic_error("Cannot write to a constant literal");

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
		// dont have em
		throw std::logic_error("Not implemented");

	case Parser::Address:
		return memory->set(parser.operand, value);

	case Parser::Constant:
		throw std::logic_error("Cannot write to a constant literal");

	case Parser::Empty:
		throw std::logic_error("Cannot write to an empty operand");

	default:
		throw std::logic_error("Unknown type");
	}
}
