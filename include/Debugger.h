#ifndef DEBUGGER_H
#define DEBUGGER_H

#include <iostream>
#include <iomanip>
#include <bitset>
#include <algorithm>

#include "Memory.h"
#include "Computer.h"

namespace Debugger {

class Instance {
protected:
	std::vector<uint16_t> breakpoints;

public:
	Computer& computer;
	bool inputting;
	int steps;
	bool exit;

	Instance(Computer& computer);
	virtual ~Instance();

	void run();
	void step();

	void handle_command(const std::string& command);
};

std::string pretty_address(uint16_t address);

template <int width>
std::string pretty_hex(uint32_t value);

void pretty_16(uint16_t value);
void pretty_8(uint8_t value);

void flag_print(uint8_t flag, const std::string name);
uint32_t make_number(std::string& input);
void terminal(Instance& instance);
}

#endif // DEBUGGER_H
