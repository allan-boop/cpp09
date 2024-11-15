#include "PmergeMe.hpp"

int main(int ac, char **av) {
	// std::string sequence[] = {"1", "9", "2", "8", "6", "7", "5", "4", "3", ""};
	// (void)av;
	if (ac < 2) {
		std::cerr << "Error: no input" << std::endl;
		return 1;
	}
	try {
		PmergeMe pmergeMe(av + 1);
		// PmergeMe pmergeMe(sequence);
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}