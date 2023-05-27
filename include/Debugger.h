#ifndef DEBUGGER_H
#define DEBUGGER_H

#include <iostream>
#include <iomanip>
#include <bitset>
#include <algorithm>

#include "Computer.h"

namespace Dbg {

void run_dbg(Computer& computer);
void handle_command(Computer& computer, std::string& command, bool& inputting, bool& single_step);
void print_reg(uint16_t value);
void flag_print(uint8_t fl, std::string name);

}

#endif // DEBUGGER_H
