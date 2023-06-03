#include "Debugger.h"

namespace Debugger {
void terminal(Instance& instance) {
	std::cout << "Copyright (c) 2023-present Maarten van Keulen MaartenvKeulen@proton.me\n"
			   << "This program and its source code are licensed under the MIT license (See LICENSE)\n"
			   << "Enter HELP for a list of commands\n";
	std::string input;

	instance.inputting = true;
	while (!instance.exit) {
		if (instance.inputting) {
			std::cout << "\n>";
			std::getline(std::cin, input);

			instance.handle_command(input);
			continue;
		}

		instance.run();
	}
}

Instance::Instance(Computer& computer) : computer(computer), inputting(false), steps(0), exit(false) {}

Instance::~Instance() {
	//dtor
}

void Instance::run() {
	step();
	if (--steps <= 0) {
		inputting = true;
		std::cout << "Paused execution at IP=" << std::hex << computer.IP;
		return;
	}

	if (!computer.running) {
		inputting = true;
		std::cout << "Computer halted at IP=" << std::hex << computer.IP;
	}
}

void Instance::step()
{
	this->computer.tick();
}

void Instance::handle_command(const std::string& command) {
	std::vector<std::string> args;
	const std::map<std::string,
	std::tuple<std::string, std::function<void()>>> commands {
		{
			"help", {"Shows a list of commands", [&commands]() {
				for (const auto& command : commands) {
					std::cout << command.first << " - " << std::get<0>(command.second) << std::endl;
				}
			}}
		},
		{
			"c", {"Continues execution", [this]() {
				computer.running = true;
				inputting = false;
			}}
		},
		{
			"s", {"[amount opt] Take a single step or a given amount of steps", [this, &args]() {
				computer.running = true;
				inputting = false;
				steps = (args.size() > 1)
					? make_number(args.at(1))
					: 1;
			}}
		},
		{
			"quit", {"Quits the debugger", [this]() {
				exit = true;
			}}
		},
		{
			"goto", {"[address] Jump to specified address", [this, &args]() {
				computer.IP = (uint16_t)make_number(args.at(1));
				std::cout << "IP"; print_reg(computer.IP);
			}}
		},
		{
			"reg", {"Display CPU registers", [this]() {
				std::cout << "IP"; print_reg(computer.IP);
				std::cout << "SP"; print_reg(computer.SP);
				std::cout << "AX"; print_reg(computer.AX);
				std::cout << "BX"; print_reg(computer.BX);
				std::cout << "CX"; print_reg(computer.CX);
				std::cout << "DX"; print_reg(computer.DX);
				std::cout << "EX"; print_reg(computer.EX);
				std::cout << "FL ";
				flag_print(computer.ZF, "ZF");
				flag_print(computer.CF, "CF");
				flag_print(computer.SF, "SF");
				flag_print(computer.IF, "IF");
			}}
		}
	};

    size_t pos = 0, prev_pos = 0;
    while (true) {
        pos = command.find(' ', prev_pos);
        if (pos == std::string::npos) {
            args.push_back(command.substr(prev_pos));
            break;
        }

        args.push_back(command.substr(prev_pos, pos - prev_pos));
        prev_pos = pos + 1;
    }

    if (args.empty()) {
		std::cout << "No such command\n";
		return;
    }

    // Name of command
    std::string& name = args.at(0);
    std::transform(name.begin(), name.end(), name.begin(),
		[](unsigned char  c) {
			return std::tolower(c);
		});

	auto it = commands.find(name);
	if (it == commands.end()) {
		std::cout << "No such command `" << name << "'\n";
		return;
	}

	try {
		std::get<1>(it->second)();
	}
	catch(const std::exception& e) {
		std::cerr << "Exception during command execution: " << e.what();
	}
}

void print_reg(uint16_t value) {
	std::bitset<16> bits(value);
	std::string binary_string = bits.to_string();
	std::string fmt_binary_string;

	for (size_t i = 0; i < binary_string.size(); i += 4) {
		fmt_binary_string += binary_string.substr(i, 4) + " ";
	}

	uint8_t char_1 = static_cast<uint8_t>((value & 0xFF00) >> 8);
	uint8_t char_2 = static_cast<uint8_t>(value & 0x00FF);

	std::cout << " 0x" << std::setfill('0') << std::setw(4) << std::hex << value << " "
			  << "0b" << fmt_binary_string
			  << "'" << static_cast<char>(char_1) << static_cast<char>(char_2) << "'"
			  << " (" << std::dec << value << ")" << std::endl;
};

void flag_print(uint8_t flag, const std::string name) {
	if (flag) {
		std::cout << name << ' ';
	}
	else {
		std::cout << "   ";
	}
};

uint32_t make_number(std::string& input) {
	std::transform(input.begin(), input.end(), input.begin(),
		[](unsigned char c) {
			return std::tolower(c);
		});

	// identify string
	if (input.rfind("0x", 0) == 0) {
		return std::stoi(input, 0, 16);
	}

	if (input.rfind("0b", 0) == 0) {
		return std::stoi(input.substr(2), 0, 2);
	}

	if (input.rfind("0", 0) == 0) {
		return std::stoi(input, 0, 8);
	}

	return std::stoi(input);
}
}
