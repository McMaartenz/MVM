#include "Port.h"

Port::Port() : connected(false), out(default_out), in(default_in)
{
	//ctor
}

Port::~Port()
{
	//dtor
}

void Port::default_out(uint8_t value) {
	std::cout << "[i] Unattached OUT: " << value << std::endl;
}

uint8_t Port::default_in() {
	std::cout << "[i] Unattached IN\n";
	return 0;
}

void Port::attach(std::function<void(uint8_t)> out, std::function<uint8_t()> in) {
	this->out = out;
	this->in = in;
}
