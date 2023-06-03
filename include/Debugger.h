#ifndef DEBUGGER_H
#define DEBUGGER_H

#include <iostream>
#include <iomanip>
#include <bitset>
#include <algorithm>

#include "Computer.h"

namespace Debugger {

class Instance {
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

void print_reg(uint16_t value);
void flag_print(uint8_t flag, const std::string name);
uint32_t make_number(std::string& input);
void terminal(Instance& instance);
}

#endif // DEBUGGER_H
