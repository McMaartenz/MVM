#include <iostream>
#include <cstdlib>
#include <filesystem>

#include "ArgumentParser.h"
#include "Computer.h"
#include "Debugger.h"
#include "Test.h"

void serial_out(uint8_t value) {
	std::cout << (char)value;
}

uint8_t serial_in() {
	char c;
	std::cin >> c;
	return c;
}

void run(Computer& computer);
void register_tests(Tester& tester);

int main(int argc, char** argv) {
	ArgumentParser::Parser* args = ArgumentParser::Initialize(argc, argv);

	std::cout << "Hello, World!\n";

	// Flag settings loading
	int memory_size = args->flag_ivalue("-m", 1024); // Memory size
	std::string disk_file_path = args->flag_value("-f"); // Disk file

	bool use_serial = args->has_flag("-s"); // Use serial
	bool use_debug = args->has_flag("-d"); // Use debugger
	bool use_tests = args->has_flag("-t"); // Use tester

	// Flag validation
	if (memory_size < 255) {
		if (memory_size <= 0) {
			std::cout << "[x] Invalid RAM settings. RAM should be >0 B\n";
			return EXIT_FAILURE;
		}

		std::cout << "[!] The computer has been given dangerously little RAM: " << memory_size << " B\n";
	}

	if (!std::filesystem::exists(disk_file_path)) {
		std::cout << "[x] Disk file could not be found, or was not specified\n";
		return EXIT_FAILURE;
	}

	Disk disk_file(disk_file_path);
	Computer computer(memory_size, &disk_file);

	if (use_serial) {
		computer.IO[0x0000].attach(serial_out, serial_in);
	}

	computer.boot();

	if (use_tests) {
		Tester tester;

		register_tests(tester);
		tester.execute_tests();
		return EXIT_SUCCESS;
	}

	if (use_debug) {
		Debugger::Instance instance(computer);
		Debugger::terminal(instance);
	}
	else {
		run(computer);
	}

	std::cout << "Computer is no longer running\n";
	return EXIT_SUCCESS;
}

void run(Computer& computer) {
	while (computer.running) {
		computer.tick();
	}
}

// Put your tests here
void register_tests(Tester& tester) {
	tester.register_test("Can run",
		[tester](Debugger::Instance& instance) {
			std::cout << "Hello from test\n";
		});
}
