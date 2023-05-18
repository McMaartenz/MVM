#ifndef DEBUGGER_H
#define DEBUGGER_H

#include <iostream>
#include <iomanip>
#include <bitset>

#include "Computer.h"

namespace Dbg {

void run_dbg(Computer& computer);
void handle_command(Computer& computer, std::string& command, bool& inputting, bool& single_step);

}

#endif // DEBUGGER_H
