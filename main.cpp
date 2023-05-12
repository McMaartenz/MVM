#include <iostream>
#include <cstdlib>

#include "ArgumentParser.h"

int main(int argc, char** argv)
{
	ArgumentParser::Parser* args = ArgumentParser::Initialize(argc, argv);

	std::cout << "Hello, World!\n";
	// Code

	return EXIT_SUCCESS;
}
