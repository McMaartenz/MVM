#include "Computer.h"

Computer::Computer(uint32_t memory_size, Disk* disk) : disk_file(disk) {
	memory = new Memory(memory_size);
}

Computer::~Computer() {
	//dtor
}

// Copy 0x000 - 0x200 from disk file to RAM, jump to [0x000]
void Computer::boot() {
	IP = 0x0000;
	SP = 0x02FF; // Give 0xFF addresses of RAM for stack until the OS initializes this

	running = true;

	disk_file->readMany(0, memory->data, 0x200);
}

void Computer::tick() {
	uint8_t first_byte = memory->data[IP];
	Opcodes::Parser parser(first_byte);

	switch (parser.opcode) {
	case MOV: {
		std::cout << "MOV!\n";
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
