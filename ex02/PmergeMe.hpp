#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>

#include <list>
#include <vector>

class PmergeMe {
	private:
		PmergeMe();
		std::list<size_t> _liContainer;
		std::list<std::pair<size_t, size_t> > _pairs;
		std::vector<size_t> _veContainer;
		PmergeMe	sortContainer();
		void	fillContainer(char *sequence[]);
		void	sortBiggest(std::list<std::pair<size_t, size_t> > & pairs, size_t beg, size_t end);
		void	merge(std::list<std::pair<size_t, size_t> > & lst, int left, int mid, int right);
		void	insertShortest();
		void	makePairs();
		void	printBeforeSort();
		size_t 	last_or_jacob();
		size_t	_lastIfOdd;
		bool	_isOdd;
	public:
		PmergeMe(char *sequence[]);
		~PmergeMe();
};

#endif