#include "Test.h"

Tester::Tester() {
	//ctor
}

Tester::~Tester() {
	//dtor
}

void Tester::register_test(const std::string name, std::function<void(Debugger::Instance&)> test) {
	tests.push_back(std::make_tuple(name, test));
}

void Tester::execute_tests() {
	for (auto& test : tests) {
		std::cout << time() << "[+] Registered test: " << std::get<0>(test) << std::endl;
	}

	std::cout << time() << "[i] Starting tests\n\n";

	int success_amount = 0;
	for (auto& test : tests) {
		try {
			RAMDisk disk(1024);
			Computer computer(1024, &disk);
			computer.boot();

			Debugger::Instance instance(computer);

			auto fn = std::get<1>(test);
			fn(instance);

			success_amount++;
			std::cout << time() << "[v] PASS - " << std::get<0>(test) << std::endl;
		}
		catch (const std::exception& e) {
			std::cout << time() << "[x] FAIL - " << std::get<0>(test) << " - " << e.what() << std::endl;
		}
	}

	std::cout << std::endl << time() << "[i] End of tests\n";
	std::cout << time() << "[i] " << success_amount << "/" << tests.size() << " tests passed\n";
}

std::string Tester::time() {
	using namespace std::chrono;

	const auto now = system_clock::now();
    const auto timepoint = time_point_cast<milliseconds>(now);
    const auto duration = timepoint.time_since_epoch();

	hours h;
	minutes m;
	seconds s;
	milliseconds ms;

	h = duration_cast<hours>(duration) % hours(24);
    m = duration_cast<minutes>(duration) % minutes(60);
    s = duration_cast<seconds>(duration) % seconds(60);
	ms = duration_cast<milliseconds>(duration) % milliseconds(1000);

    std::ostringstream oss;
    oss << "[";
	oss << std::setfill('0') << std::setw(2) << h.count() << ":"
        << std::setfill('0') << std::setw(2) << m.count() << ":"
        << std::setfill('0') << std::setw(2) << s.count() << "."
        << std::setfill('0') << std::setw(3) << ms.count() << "z] ";

	return oss.str();
}
