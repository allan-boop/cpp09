#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>

#include <deque>
#include <vector>

class PmergeMe {
	private:
		PmergeMe();
		std::deque<size_t> _deContainer;
		std::deque<std::pair<size_t, size_t> > _pairs;
		std::vector<std::pair<size_t, size_t> > _pairsVe;
		std::vector<size_t> _veContainer;
		std::vector<size_t> _jacob;
		std::deque<size_t> _jacobDe;
		PmergeMe	sortContainer();
		void	fillContainer(char *sequence[]);
		void	sortBiggestDe(std::deque<std::pair<size_t, size_t> > & pairs, size_t beg, size_t end);
		void	mergeDe(std::deque<std::pair<size_t, size_t> > & lst, int left, int mid, int right);
		void	jacobDeMem();
		void	insertDeShortest();
		void	makePairs();
		void	printBeforeSort();
		size_t 	last_or_jacobDe();
		void 	insertDeAlgo(size_t numberToInsert);
		size_t	_lastIfOdd;
		bool	_isOdd;
		void	sortBiggestVe(std::vector<std::pair<size_t, size_t> > & pairs, size_t beg, size_t end);
		void	mergeVe(std::vector<std::pair<size_t, size_t> > & lst, int left, int mid, int right);
		void	jacobVeMem();
		void	insertVeShortest();
		size_t 	last_or_jacobVe();
		void 	insertVeAlgo(size_t numberToInsert);
		void	makeVePairs();
	public:
		PmergeMe(char *sequence[]);
		~PmergeMe();
};

#endif