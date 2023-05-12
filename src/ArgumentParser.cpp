#include "ArgumentParser.h"

ArgumentParser::Parser::Parser(int argc, char** argv) : argc(argc), argv(argv) {}
void ArgumentParser::Parser::dbg_print() {
	for (int i = 0; i < argc; i++) {
		std::cout << argv[i] << std::endl;
	}
}

bool ArgumentParser::Parser::has_flag(const char* name) const {
	return std::any_of(argv, argv + argc, [name](const char* arg) {
		return std::strcmp(arg, name) == 0;
	});
}

std::string ArgumentParser::Parser::flag_value(const char* name) const {
	auto arg_iter = std::find_if(argv, argv + argc, [name](const char* arg) {
		return std::strcmp(arg, name) == 0;
	});

	if (arg_iter >= argv + argc - 1) {
		return ""; // Not found
	}

	return arg_iter[1];
}

int ArgumentParser::Parser::flag_ivalue(const char* name, int default_value) const {
	try {
		return std::stoi(flag_value(name));
	}
	catch (std::invalid_argument const&) {
		return default_value;
	}
}

ArgumentParser::Parser* ArgumentParser::Initialize(int argc, char** argv) {
	return new Parser(argc, argv);
}
