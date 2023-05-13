#ifndef COMPUTER_H
#define COMPUTER_H

#include "Memory.h"
#include "Disk.h"
#include "Opcodes.h"

class Computer
{
	public:
		Memory* memory;
		Disk* disk_file;

		bool running;

		// Registers
		uint32_t IP;
		uint32_t SP;

		Computer(uint32_t memory_size, Disk* disk);
		virtual ~Computer();

		void boot();
		void tick();

	protected:

	private:
};

#endif // COMPUTER_H
