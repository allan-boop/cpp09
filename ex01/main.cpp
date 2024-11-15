#include "RPN.hpp"
#include "iostream"

int main (int ac, char **av)
{
	if (ac != 2) {
		std::cout << "ERROR: invalid input" << std::endl;
		return 0;
	}

	try {
		RPN nStack(av[1]);
	} catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
}