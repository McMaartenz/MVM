#include "Test.h"

Tester::Tester() {
	//ctor
}

Tester::~Tester() {
	//dtor
}

void Tester::register_test(const std::string& name, std::function<void(Debugger::Instance&)> test) {
	tests.push_back(std::make_tuple(name, test));
}

void Tester::execute_tests() {

}
