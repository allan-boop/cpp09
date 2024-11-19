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
	std::cout << "Before: ";
	for (std::deque<size_t>::iterator it = _deContainer.begin(); it != _deContainer.end(); it++) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

void	PmergeMe::fillContainer(char *sequence[]) {
	_isOdd = false;
	for (int i = 0; sequence[i]; i++) {
		if (sequence[i][0] != '\0' && atol(sequence[i]) != 0 && sequence[i][0] != '-') {
			_veContainer.push_back(atol(sequence[i]));
			_deContainer.push_back(atol(sequence[i]));
		} else {
			throw std::invalid_argument("Error: invalid input, only positive numbers are allowed");
		}
	}
	if (_veContainer.size() % 2 != 0) {
		_isOdd = true;
		_lastIfOdd = _veContainer.back();
	}
}

void	PmergeMe::mergeVe(std::vector<std::pair<size_t, size_t> > & lst, int left, int mid, int right)  {
	std::vector<std::pair<size_t, size_t> >::iterator itI = lst.begin();
	std::vector<std::pair<size_t, size_t> >::iterator itJ = lst.begin();
	std::vector<std::pair<size_t, size_t> >::iterator itChange = lst.begin();
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

void	PmergeMe::mergeDe(std::deque<std::pair<size_t, size_t> > & lst, int left, int mid, int right)  {
	std::deque<std::pair<size_t, size_t> >::iterator itI = lst.begin();
	std::deque<std::pair<size_t, size_t> >::iterator itJ = lst.begin();
	std::deque<std::pair<size_t, size_t> >::iterator itChange = lst.begin();
	std::deque<int> tempFir(right - left + 1);
	std::deque<int> tempSec(right - left + 1);

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

void PmergeMe::sortBiggestVe(std::vector<std::pair<size_t, size_t> > & pairsVe, size_t beg, size_t end) {
	int mid;
	if (beg < end)
	{
		mid = (beg+end)/2;
		sortBiggestVe(pairsVe, beg, mid);
		sortBiggestVe(pairsVe, mid+1, end);
		mergeVe(pairsVe, beg, mid, end);
	}
}

void PmergeMe::sortBiggestDe(std::deque<std::pair<size_t, size_t> > & pairs, size_t beg, size_t end) {
	int mid;
	if (beg < end)
	{
		mid = (beg+end)/2;
		sortBiggestDe(pairs, beg, mid);
		sortBiggestDe(pairs, mid+1, end);
		mergeDe(pairs, beg, mid, end);
	}
}

size_t PmergeMe::last_or_jacobVe() {
	size_t n1 = 1;
	size_t n2 = 1;
	size_t result = 0;

	while (result < _pairsVe.size()) {
		result = n1 + (n2 * 2);
		if (result == _pairsVe.size())
			return result;
		n2 = n1;
		n1 = result;
	}
	return _pairsVe.size();
}

size_t PmergeMe::last_or_jacobDe() {
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

void PmergeMe::jacobVeMem() {
	size_t n1 = 1;
	size_t n2 = 1;
	size_t result = 0;

	result = n1 + (n2 * 2);
	while (result < _pairsVe.size()) {
		_jacob.push_back(result - 1);
		n2 = n1;
		n1 = result;
		result = n1 + (n2 * 2);
	}
	_jacob.push_back(_pairsVe.size() - 1);
}

void PmergeMe::jacobDeMem() {
	size_t n1 = 1;
	size_t n2 = 1;
	size_t result = 0;

	result = n1 + (n2 * 2);
	while (result < _pairs.size()) {
		_jacobDe.push_back(result - 1);
		n2 = n1;
		n1 = result;
		result = n1 + (n2 * 2);
	}
	_jacobDe.push_back(_pairs.size() - 1);
}

void PmergeMe::insertVeAlgo(size_t numberToInsert) {
	size_t dicMax = 0;
	size_t dicMin = 0;
	size_t result = 0;
	size_t k = 0;

	dicMax = _veContainer.size() - 1;
	result = (dicMax - dicMin) / 2;
	k = result;
	while (!(numberToInsert < _veContainer[k + 1] && numberToInsert > _veContainer[k])) {
		if (numberToInsert < _veContainer[k]) {
			dicMax = k;
			result -= (dicMax - dicMin) / 2;
		} else if (numberToInsert > _veContainer[k]) {
			dicMin = k;
			result += (dicMax - dicMin) / 2;
		}
		k = result;
		if ((dicMin == 0 && dicMax == 1) || (dicMin == _veContainer.size() - 2 && dicMax == _veContainer.size() - 1)) {
			break;
		}
	}
	if (dicMin == 0 && dicMax == 1) {
		if (numberToInsert < _veContainer[0]) {
			_veContainer.insert(_veContainer.begin(), numberToInsert);
		} else {
			_veContainer.insert(_veContainer.begin() + 1, numberToInsert);
		}
	} else if ((dicMin == _veContainer.size() - 2 && dicMax == _veContainer.size() - 1)) {
		_veContainer.insert(_veContainer.end(), numberToInsert);
	} else {
		_veContainer.insert(_veContainer.begin() + (k + 1), numberToInsert);
	}
}

void PmergeMe::insertDeAlgo(size_t numberToInsert) {
	size_t dicMax = 0;
	size_t dicMin = 0;
	size_t result = 0;
	size_t k = 0;

	dicMax = _deContainer.size() - 1;
	result = (dicMax - dicMin) / 2;
	k = result;
	while (!(numberToInsert < _deContainer[k + 1] && numberToInsert > _deContainer[k])) {
		if (numberToInsert < _deContainer[k]) {
			dicMax = k;
			result -= (dicMax - dicMin) / 2;
		} else if (numberToInsert > _deContainer[k]) {
			dicMin = k;
			result += (dicMax - dicMin) / 2;
		}
		k = result;
		if ((dicMin == 0 && dicMax == 1) || (dicMin == _deContainer.size() - 2 && dicMax == _deContainer.size() - 1)) {
			break;
		}
	}
	if (dicMin == 0 && dicMax == 1) {
		if (numberToInsert < _deContainer[0]) {
			_deContainer.insert(_deContainer.begin(), numberToInsert);
		} else {
			_deContainer.insert(_deContainer.begin() + 1, numberToInsert);
		}
	} else if ((dicMin == _deContainer.size() - 2 && dicMax == _deContainer.size() - 1)) {
		_deContainer.insert(_deContainer.end(), numberToInsert);
	} else {
		_deContainer.insert(_deContainer.begin() + (k + 1), numberToInsert);
	}
}

void PmergeMe::insertVeShortest() {
	size_t lastLittlePushed = 0;
	size_t i = 0;
	size_t j = 0;
	size_t stopBigShort = 0;
	size_t nextLimit = 0;

	jacobVeMem();
	_veContainer.clear();
	_veContainer.push_back(_pairsVe[i].second);
	lastLittlePushed = i;
	_veContainer.push_back(_pairsVe[i].first);
	i++;
	_veContainer.push_back(_pairsVe[i].first);
	stopBigShort = _jacob.size();
	j = 0;
	while (j < stopBigShort) {
		i = _jacob[j];
		while (i > lastLittlePushed) {
			insertVeAlgo(_pairsVe[i].second);
			i--;
		}
		lastLittlePushed = _jacob[j];
		i = _jacob[j];
		if (j == stopBigShort - 1)
			nextLimit = _pairsVe.size() - 1;
		else
			nextLimit = _jacob[j + 1];
		while (i < nextLimit) {
			_veContainer.push_back(_pairsVe[i].first);
			i++;
		}
		j++;
	}
	if (_pairsVe.size() > 2)
	_veContainer.push_back(_pairsVe[_pairsVe.size() - 1].first);
	if (_isOdd) {
		insertVeAlgo(_lastIfOdd);
	}
}

void PmergeMe::insertDeShortest() {
	size_t lastLittlePushed = 0;
	size_t i = 0;
	size_t j = 0;
	size_t stopBigShort = 0;
	size_t nextLimit = 0;

	jacobDeMem();
	_deContainer.clear();
	_deContainer.push_back(_pairs[i].second);
	lastLittlePushed = i;
	_deContainer.push_back(_pairs[i].first);
	i++;
	_deContainer.push_back(_pairs[i].first);
	stopBigShort = _jacobDe.size();
	j = 0;
	while (j < stopBigShort) {
		i = _jacobDe[j];
		while (i > lastLittlePushed) {
			insertDeAlgo(_pairs[i].second);
			i--;
		}
		lastLittlePushed = _jacobDe[j];
		i = _jacobDe[j];
		if (j == stopBigShort - 1)
			nextLimit = _pairs.size() - 1;
		else
			nextLimit = _jacobDe[j + 1];
		while (i < nextLimit) {
			_deContainer.push_back(_pairs[i].first);
			i++;
		}
		j++;
	}
	if (_pairs.size() > 2)
	_deContainer.push_back(_pairs[_pairs.size() - 1].first);
	if (_isOdd) {
		insertDeAlgo(_lastIfOdd);
	}
}

void PmergeMe::makeVePairs() {
	std::vector<size_t>::iterator it;
	std::vector<size_t>::iterator itNext;

	if (_isOdd)
		_veContainer.pop_back();
	for (it = _veContainer.begin(); it != _veContainer.end(); it++) {
		itNext = it;
		itNext++;
		if (itNext != _veContainer.end()) {
			if (*it > *itNext)
				_pairsVe.push_back(std::make_pair(*it++, *itNext));
			else if (*it < *itNext)
				_pairsVe.push_back(std::make_pair(*itNext, *it++));
		}
	}
	if (_veContainer.size() > 3) {
		sortBiggestVe(_pairsVe, 0, _pairsVe.size() - 1);
		insertVeShortest();
	} else if (_veContainer.size() > 1) {
		size_t *numbTab = new size_t[3];
		size_t i = 0;
		while (_veContainer.back()) {
			numbTab[i] = _veContainer.back();
			_veContainer.pop_back();
			i++;
		}
		_veContainer.clear();
		_veContainer.insert(_veContainer.begin(), numbTab[0]);
		if (numbTab[0] > numbTab[1]) {
			_veContainer.insert(_veContainer.begin(), numbTab[1]);
		} else {
			_veContainer.insert(_veContainer.begin() + 1, numbTab[1]);
		}
		if (i == 3) {
			if (_lastIfOdd < _veContainer[0]) {
				_veContainer.insert(_veContainer.begin(), _lastIfOdd);
			} else if (_lastIfOdd < _veContainer[1]) {
				_veContainer.insert(_veContainer.begin() + 1, _lastIfOdd);
			} else {
				_veContainer.insert(_veContainer.end(), _lastIfOdd);
			}
		}
	}
}

void PmergeMe::makePairs() {
	std::deque<size_t>::iterator it;
	std::deque<size_t>::iterator itNext;

	if (_isOdd)
		_deContainer.pop_back();
	for (it = _deContainer.begin(); it != _deContainer.end(); it++) {
		itNext = it;
		itNext++;
		if (itNext != _deContainer.end()) {
			if (*it > *itNext)
				_pairs.push_back(std::make_pair(*it++, *itNext));
			else if (*it < *itNext)
				_pairs.push_back(std::make_pair(*itNext, *it++));
		}
	}
	if (_deContainer.size() > 3) {
		sortBiggestDe(_pairs, 0, _pairs.size() - 1);
		insertDeShortest();
	} else if (_deContainer.size() > 1) {
		size_t *numbTab = new size_t[3];
		size_t i = 0;
		while (_deContainer.front()) {
			numbTab[i] = _deContainer.front();
			_deContainer.pop_front();
			i++;
		}
		_deContainer.clear();
		_deContainer.insert(_deContainer.begin(), numbTab[0]);
		if (numbTab[0] > numbTab[1]) {
			_deContainer.insert(_deContainer.begin(), numbTab[1]);
		} else {
			_deContainer.insert(_deContainer.begin() + 1, numbTab[1]);
		}
		if (i == 3) {
			if (_lastIfOdd < _deContainer[0]) {
				_deContainer.insert(_deContainer.begin(), _lastIfOdd);
			} else if (_lastIfOdd < _deContainer[1]) {
				_deContainer.insert(_deContainer.begin() + 1, _lastIfOdd);
			} else {
				_deContainer.insert(_deContainer.end(), _lastIfOdd);
			}
		}
	}
}

PmergeMe	PmergeMe::sortContainer() {
	double	timeVec = 0;
	double	timeDeq = 0;

	clock_t start = clock();
	makePairs();
	clock_t end = clock();
	timeDeq = (double)(end - start) / CLOCKS_PER_SEC;

	start = clock();
	makeVePairs();
	end = clock();
	timeVec = (double)(end - start) / CLOCKS_PER_SEC;

	std::cout << "After: ";
	for (std::deque<size_t>::iterator it = _deContainer.begin(); it != _deContainer.end(); it++) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
	std::cout << "Time to process a range of " << _deContainer.size() << " elements with std::deque : " << std::fixed << timeDeq << " seconds." << std::endl;
	std::cout << "Time to process a range of " << _veContainer.size() << " elements with std::vector : " << std::fixed << timeVec << " seconds." << std::endl;

	return *this;
}