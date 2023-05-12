#ifndef ARGUMENTPARSER_H
#define ARGUMENTPARSER_H

#include <iostream>
#include <algorithm>
#include <cstring>

namespace ArgumentParser {
	class Parser {
		int argc;
		char** argv;

	public:
		Parser(int argc, char** argv);

		void dbg_print();
		bool has_flag(const char* name) const;
		std::string flag_value(const char* name) const;
		int flag_ivalue(const char* name, int default_value = 0) const;
	};

	Parser* Initialize(int argc, char** argv);
};

#endif // ARGUMENTPARSER_H
