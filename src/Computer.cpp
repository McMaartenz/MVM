#include "Computer.h"

Computer::Computer(uint32_t memory_size, Disk* disk) : disk_file(disk)
{
	memory = new Memory(memory_size);
}

Computer::~Computer()
{
	//dtor
}

// Copy 0x000 - 0x200 from disk file to RAM, jump to [0x000]
void Computer::boot() {
	IP = 0x0000;


}
