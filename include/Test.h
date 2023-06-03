#ifndef TEST_H
#define TEST_H

#include <vector>
#include <tuple>

#include "Debugger.h"

class Tester {
public:
	Tester();
	virtual ~Tester();

	void register_test(const std::string& name, std::function<void(Debugger::Instance&)> test);
	void execute_tests();

private:
	std::vector<
		std::tuple<
			const std::string&,
			std::function<void(Debugger::Instance&)>
	>> tests;
};

#endif // TEST_H
