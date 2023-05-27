#include "Debugger.h"

void Dbg::run_dbg(Computer& computer) {
	std::cout << "Copyright (c) 2023-present Maarten van Keulen MaartenvKeulen@proton.me\nThis program and its source code are licensed under the MIT license (See LICENSE)\nEnter HELP for a list of commands";
	std::string input;

	bool inputting = true;
	bool single_step = false;
	while (true) {
		while (inputting) {
			std::cout << "\n>";
			std::getline(std::cin, input);

			handle_command(computer, input, inputting, single_step);
		}

		computer.tick();
		if (single_step) {
			inputting = true;
			single_step = false;
		}

		if (!computer.running) {
			inputting = true;
			std::cout << "Computer stopped at IP=" << std::hex << computer.IP;
		}
	}
}

void Dbg::handle_command(Computer& computer, std::string& command, bool& inputting, bool& single_step) {
	std::vector<std::string> args;
	const std::map<std::string,
	std::tuple<std::string, std::function<void(Computer&)>>> commands {
		{
			"help", {"Shows a list of commands", [&commands](Computer& c) {
				for (const auto& command : commands) {
					std::cout << command.first << " - " << std::get<0>(command.second) << std::endl;
				}
			}}
		},
		{
			"c", {"Continues execution", [&inputting](Computer& c) {
				c.running = true;
				inputting = false;
			}}
		},
		{
			"s", {"Take a single step", [&inputting, &single_step](Computer& c) {
				c.running = true;
				single_step = true;
				inputting = false;
			}}
		},
		{
			"quit", {"Quits the debugger", [](Computer& c) {
				std::exit(EXIT_SUCCESS);
			}}
		},
		{
			"goto", {"[address] Jump to specified address", [&args](Computer& c) {
				c.IP = (uint16_t)std::stoi(args[1]);
				std::cout << "IP"; print_reg(c.IP);
			}}
		},
		{
			"reg", {"Display CPU registers", [](Computer& c) {
				std::cout << "IP"; print_reg(c.IP);
				std::cout << "SP"; print_reg(c.SP);
				std::cout << "AX"; print_reg(c.AX);
				std::cout << "BX"; print_reg(c.BX);
				std::cout << "CX"; print_reg(c.CX);
				std::cout << "DX"; print_reg(c.DX);
				std::cout << "EX"; print_reg(c.EX);
				std::cout << "FL ";
				flag_print(c.ZF, "ZF");
				flag_print(c.CF, "CF");
				flag_print(c.SF, "SF");
				flag_print(c.IF, "IF");
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

    std::transform(args[0].begin(), args[0].end(), args[0].begin(),
		[](unsigned char  c) {
			return std::tolower(c);
		});

	auto it = commands.find(args[0]);
	if (it == commands.end()) {
		std::cout << "No such command `" << args[0] << "'\n";
		return;
	}

	try {
		std::get<1>(it->second)(computer);
	}
	catch(const std::exception& e) {
		std::cerr << "Exception during command execution: " << e.what();
	}
}

void Dbg::print_reg(uint16_t value) {
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

void Dbg::flag_print(uint8_t fl, std::string name) {
	if (fl) {
		std::cout << name << ' ';
	}
	else {
		std::cout << "   ";
	}
};
