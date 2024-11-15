#include "BitcoinExchange.hpp"

int main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cerr << "ERROR: Wrong input patern ./bitcoin [filename]" << std::endl;
		return 1;
	}

	try{

		BitcoinExchange exchange(av[1]);
	}
	catch(const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}