#include "PmergeMe.hpp"
#include <iterator>
#include <iostream>
#include <stdlib.h>
#include <stdlib.h>
#include <unistd.h>

PmergeMe::PmergeMe(char *sequence[]) {
	try {
		fillContainer(sequence);
		printBeforeSort();
		sortContainer();
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
}

PmergeMe::~PmergeMe() {

}

void	PmergeMe::printBeforeSort() {
	std::cout << "Before sort:" << std::endl;
	std::cout << "list: ";
	for (std::deque<size_t>::iterator it = _liContainer.begin(); it != _liContainer.end(); it++) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
	std::cout << "vector: ";
	for (std::vector<size_t>::iterator it = _veContainer.begin(); it != _veContainer.end(); it++) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
	if (_isOdd) {
		_veContainer.pop_back();
		_liContainer.pop_back();
	}
}

void	PmergeMe::fillContainer(char *sequence[]) {
	_isOdd = false;
	for (int i = 0; sequence[i]; i++) {
		if (sequence[i][0] != '\0' && atol(sequence[i]) != 0 && sequence[i][0] != '-') {
			_veContainer.push_back(atol(sequence[i]));
			_liContainer.push_back(atol(sequence[i]));
		} else {
			throw std::invalid_argument("Error: invalid input, only positive numbers are allowed");
		}
	}
	if (_veContainer.size() % 2 != 0) {
		_isOdd = true;
		_lastIfOdd = _veContainer.back();
	}
}

void	PmergeMe::merge(std::deque<std::pair<size_t, size_t> > & lst, int left, int mid, int right)  {
	std::deque<std::pair<size_t, size_t> >::iterator itI = lst.begin();
	std::deque<std::pair<size_t, size_t> >::iterator itJ = lst.begin();
	std::deque<std::pair<size_t, size_t> >::iterator itChange = lst.begin();
	std::vector<int> tempFir(right - left + 1);
	std::vector<int> tempSec(right - left + 1);

	int i = left, j = mid+1, k = 0;
	for (int h = 0; h < j; h++) {
		itJ++;
	}
	for (int h = 0; h < i; h++) {
		itI++;
	}
	while (i <= mid && j <= right) {
		if (itI->first <= itJ->first) {
			tempFir[k] = itI->first;
			tempSec[k++] = itI->second;
			itI++;
			i++;
		} else {
			tempFir[k] = itJ->first;
			tempSec[k++] = itJ->second;
			itJ++;
			j++;
		}
	}
	while (i <= mid) {
		tempFir[k] = itI->first;
		tempSec[k++] = itI->second;
		itI++;
		i++;
	}
	while (j <= right) {
		tempFir[k] = itJ->first;
		tempSec[k++] = itJ->second;
		itJ++;
		j++;
	}
	for (int p = 0; p < left; p++) {
		itChange++;
	}
	for (int p = 0; p < k; p++) {
		itChange->first = tempFir[p];
		itChange->second = tempSec[p];
		itChange++;
	}
}

void PmergeMe::sortBiggest(std::deque<std::pair<size_t, size_t> > & pairs, size_t beg, size_t end) {
	int mid;
	if (beg < end)
	{
		mid = (beg+end)/2;
		sortBiggest(pairs, beg, mid);
		sortBiggest(pairs, mid+1, end);
		merge(pairs, beg, mid, end);
	}
}

size_t PmergeMe::last_or_jacob() {
	size_t n1 = 1;
	size_t n2 = 1;
	size_t result = 0;

	while (result < _pairs.size()) {
		result = n1 + (n2 * 2);
		if (result == _pairs.size())
			return result;
		n2 = n1;
		n1 = result;
	}
	return _pairs.size();
}

void PmergeMe::jacobMem() {
	size_t n1 = 1;
	size_t n2 = 1;
	size_t result = 0;

	result = n1 + (n2 * 2);
	while (result < _pairs.size()) {
		_jacob.push_back(result - 1);
		n2 = n1;
		n1 = result;
		result = n1 + (n2 * 2);
	}
	_jacob.push_back(_pairs.size() - 1);
}

void PmergeMe::insertAlgo(size_t numberToInsert) {
	size_t dicMax = 0;
	size_t dicMin = 0;
	size_t result = 0;
	size_t k = 0;

	dicMax = _liContainer.size() - 1;
	result = (dicMax - dicMin) / 2;
	k = result;
	while (!(numberToInsert < _liContainer[k + 1] && numberToInsert > _liContainer[k])) {
		if (numberToInsert < _liContainer[k]) {
			dicMax = k;
			result -= (dicMax - dicMin) / 2;
		} else if (numberToInsert > _liContainer[k]) {
			dicMin = k;
			result += (dicMax - dicMin) / 2;
		}
		k = result;
		if ((dicMin == 0 && dicMax == 1) || (dicMin == _liContainer.size() - 2 && dicMax == _liContainer.size() - 1)) {
			break;
		}
	}
	if (dicMin == 0 && dicMax == 1) {
		if (numberToInsert < _liContainer[0]) {
			_liContainer.insert(_liContainer.begin(), numberToInsert);
		} else {
			_liContainer.insert(_liContainer.begin() + 1, numberToInsert);
		}
	} else if ((dicMin == _liContainer.size() - 2 && dicMax == _liContainer.size() - 1)) {
		_liContainer.insert(_liContainer.end(), numberToInsert);
	} else {
		_liContainer.insert(_liContainer.begin() + (k + 1), numberToInsert);
	}
}


void PmergeMe::insertShortest() {
	size_t lastLittlePushed = 0;
	size_t i = 0;
	size_t j = 0;
	size_t stopBigShort = 0;
	size_t nextLimit = 0;

	jacobMem();
	_liContainer.clear();
	_liContainer.push_back(_pairs[i].second);
	lastLittlePushed = i;
	_liContainer.push_back(_pairs[i].first);
	i++;
	_liContainer.push_back(_pairs[i].first);
	stopBigShort = _jacob.size();
	j = 0;
	while (j < stopBigShort) {
		i = _jacob[j];
		while (i > lastLittlePushed) {
			insertAlgo(_pairs[i].second);
			i--;
		}
		lastLittlePushed = _jacob[j];
		i = _jacob[j];
		if (j == stopBigShort - 1)
			nextLimit = _pairs.size() - 1;
		else
			nextLimit = _jacob[j + 1];
		while (i < nextLimit) {
			_liContainer.push_back(_pairs[i].first);
			i++;
		}
		j++;
	}
	if (_pairs.size() > 2)
	_liContainer.push_back(_pairs[_pairs.size() - 1].first);
	if (_isOdd) {
		insertAlgo(_lastIfOdd);
	}
}

void PmergeMe::makePairs() {
	std::deque<size_t>::iterator it;
	std::deque<size_t>::iterator itNext;
	for (it = _liContainer.begin(); it != _liContainer.end(); it++) {
		itNext = it;
		itNext++;
		if (itNext != _liContainer.end()) {
			if (*it > *itNext)
				_pairs.push_back(std::make_pair(*it++, *itNext));
			else if (*it < *itNext)
				_pairs.push_back(std::make_pair(*itNext, *it++));
		}
	}
	if (_liContainer.size() > 3) {
		sortBiggest(_pairs, 0, _pairs.size() - 1);
		insertShortest();
	}
	std::cout << "after:" << std::endl;
	for (std::deque<size_t>::iterator it = _liContainer.begin(); it != _liContainer.end(); it++) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

PmergeMe	PmergeMe::sortContainer() {
	makePairs();
	return *this;
}