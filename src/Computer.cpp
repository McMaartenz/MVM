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

	uint8_t buffer[512]{0};
	disk_file->read_many(0, buffer, 0x200);
	memory->write_buffer(0, buffer, 0x200);
}

void Computer::tick() {
	uint8_t byte_1, byte_2, byte_3;

	try {
		byte_1 = memory->get(IP);     // Opcode and options
		byte_2 = memory->get(IP + 1); // Registers, constant, or empty
		byte_3 = memory->get(IP + 2); // Constant or empty
	} catch(const std::out_of_range& e) {
		// TODO: Throw BUS error interrupt
		std::cout << "BUS error thrown at IP=" << std::hex << IP << std::endl;
		running = false;
		return;
	}

	Opcodes::Parser parser(byte_1);

	switch (parser.opcode) {
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
	switch (parser.selection) {
	case Opcodes::no_arguments: {
		IP += 1;
		break;
	}

	case Opcodes::reg_reg:
	case Opcodes::just_im8:
	case Opcodes::just_reg:
	case Opcodes::just_mem: {
		IP += 2;
		break;
	}

	case Opcodes::reg_mem:
	case Opcodes::mem_reg:
	case Opcodes::reg_im8: {
		IP += 3;
		break;
	}
	}
}
