#ifndef PORT_H
#define PORT_H

#include <cstdint>
#include <functional>
#include <iostream>

class Port {
  public:
	Port();
	virtual ~Port();

	bool connected;

	std::function<void(uint8_t)> out;
	std::function<uint8_t()> in;

	void attach(std::function<void(uint8_t)> out, std::function<uint8_t()> in);

  protected:

  private:
  	static void default_out(uint8_t value);
  	static uint8_t default_in();
};

#endif // PORT_H
