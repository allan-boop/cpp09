#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>

#include <deque>
#include <vector>

class PmergeMe {
	private:
		PmergeMe();
		std::deque<size_t> _liContainer;
		std::deque<std::pair<size_t, size_t> > _pairs;
		std::vector<size_t> _veContainer;
		std::vector<size_t> _jacob;
		PmergeMe	sortContainer();
		void	fillContainer(char *sequence[]);
		void	sortBiggest(std::deque<std::pair<size_t, size_t> > & pairs, size_t beg, size_t end);
		void	merge(std::deque<std::pair<size_t, size_t> > & lst, int left, int mid, int right);
		void	jacobMem();
		void	insertShortest();
		void	makePairs();
		void	printBeforeSort();
		size_t 	last_or_jacob();
		void 	insertAlgo(size_t numberToInsert);
		size_t	_lastIfOdd;
		bool	_isOdd;
	public:
		PmergeMe(char *sequence[]);
		~PmergeMe();
};

#endif