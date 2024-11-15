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
	for (std::list<size_t>::iterator it = _liContainer.begin(); it != _liContainer.end(); it++) {
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

void	PmergeMe::merge(std::list<std::pair<size_t, size_t> > & lst, int left, int mid, int right)  {
	std::list<std::pair<size_t, size_t> >::iterator itI = lst.begin();
	std::list<std::pair<size_t, size_t> >::iterator itJ = lst.begin();
	std::list<std::pair<size_t, size_t> >::iterator itChange = lst.begin();
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

void PmergeMe::sortBiggest(std::list<std::pair<size_t, size_t> > & pairs, size_t beg, size_t end) {
	int mid;
	if (beg < end)
	{
		mid = (beg+end)/2;
		sortBiggest(pairs, beg, mid);
		sortBiggest(pairs, mid+1, end);
		merge(pairs, beg, mid, end);
	}
}

size_t returnJacob(size_t last, size_t prevLast) {
	return (last + (prevLast * 2));
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

void PmergeMe::insertShortest() {
	size_t last = 1;
	size_t prevLast = 1;
	size_t tmp = 0;
	std::list<std::pair<size_t, size_t> >::iterator it = _pairs.begin();
	std::list<size_t>::iterator itForInsert;
	std::list<size_t>::iterator itForInsertNext;
	size_t i = 0;
	size_t jacob = 0;
	size_t lastLittlePushed = 0;
	size_t highLimit = 0;
	size_t lowLimit = 0;
	size_t result = 0;


	_liContainer.clear();
	_liContainer.push_back(it->second);
	lastLittlePushed = i;
	_liContainer.push_back(it->first);
	i++;
	it++;
	_liContainer.push_back(it->first);
	// boucle qui insert tout les petits dans les grands
	while (i <= last_or_jacob()) {
		// Insert en mixant les grands et les petits
			//push les petis
		jacob = returnJacob(last, prevLast) - 1;
		// 		if (jacob > _pairs.size())
		// 	jacob = _pairs.size() - 1;
		// it = _pairs.begin();
		// std::advance(it, jacob);
		// std::cout << "i: " << jacob << " " << i << " " << jacob - i << " " << it->second << std::endl;
		// i = jacob;
		std::advance(it, jacob - i);
		std::cout << "i: " << jacob << " " << i  << jacob - i << " " << it->second << std::endl;
		i = jacob;
		while (i <= last_or_jacob() && i > lastLittlePushed) {
			lowLimit = 0;
			highLimit = _liContainer.size() - 1;
			result = (highLimit - lowLimit) / 2;
			itForInsert = _liContainer.begin();
			std::advance(itForInsert, result);
			itForInsertNext = itForInsert;
			itForInsertNext++;
			while (!(it->second < *itForInsertNext && it->second > *itForInsert)) {
				if (it->second < *itForInsert) {
					highLimit = result;
					result -= ((highLimit - lowLimit) / 2);
				} else if (it->second > *itForInsert) {
					lowLimit = result;
					result += ((highLimit - lowLimit) / 2);
				}
				itForInsert = _liContainer.begin();
				std::advance(itForInsert, result);
				itForInsertNext = itForInsert;
				itForInsertNext++;
				if ((lowLimit == 0 && highLimit == 1) || (lowLimit == _liContainer.size() - 2 && highLimit == _liContainer.size() - 1)) {
					itForInsertNext = _liContainer.end();
					break;
				}
			}
			if (lowLimit == 0 && highLimit == 1) {
				itForInsertNext = _liContainer.begin();
				if (it->second < *itForInsertNext) {
					_liContainer.insert(_liContainer.begin(), it->second);
				} else {
					_liContainer.insert(itForInsert, it->second);
				}
			} else {
				_liContainer.insert(itForInsertNext, it->second);
			}
			it--;
			i--;
		}
		lastLittlePushed = jacob;
		std::advance(it, jacob - i);
		i = jacob;
		//push les grands
		while (i < returnJacob(jacob + 1, last) - 1 && i < _pairs.size() && i < last_or_jacob()) {
			_liContainer.push_back(it->first);
			it++;
			i++;
			if (it == _pairs.end()) {
				if (_isOdd) {
					// Insertion du dernier element
					lowLimit = 0;
					highLimit = _liContainer.size() - 1;
					result = (highLimit - lowLimit) / 2;
					itForInsert = _liContainer.begin();
					std::advance(itForInsert, result);
					itForInsertNext = itForInsert;
					itForInsertNext++;
					while (!(_lastIfOdd < *itForInsertNext && _lastIfOdd > *itForInsert)) {
						if (_lastIfOdd < *itForInsert) {
							highLimit = result;
							result -= ((highLimit - lowLimit) / 2);
						} else if (_lastIfOdd > *itForInsert) {
							lowLimit = result;
							result += ((highLimit - lowLimit) / 2);
						}
						itForInsert = _liContainer.begin();
						std::advance(itForInsert, result);
						itForInsertNext = itForInsert;
						itForInsertNext++;
						if ((lowLimit == 0 && highLimit == 1) || (lowLimit == _liContainer.size() - 2 && highLimit == _liContainer.size() - 1)) {
							itForInsertNext = _liContainer.end();
							break;
						}
					}
					if (lowLimit == 0 && highLimit == 1) {
						itForInsertNext = _liContainer.begin();
						if (_lastIfOdd < *itForInsertNext) {
							_liContainer.insert(_liContainer.begin(), _lastIfOdd);
						} else {
							_liContainer.insert(itForInsert, _lastIfOdd);
						}
					} else {
						_liContainer.insert(itForInsertNext, _lastIfOdd);
					}
				}
			}
		}
		// Preparer prochaine boucle
		tmp = prevLast;
		prevLast = last;
		last = returnJacob(last, tmp);
	}
}

void PmergeMe::makePairs() {
	std::list<size_t>::iterator it;
	std::list<size_t>::iterator itNext;
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
	sortBiggest(_pairs, 0, _pairs.size() - 1);
	// print pairs
	std::cout << "pairs: ";
	for (std::list<std::pair<size_t, size_t> >::iterator it = _pairs.begin(); it != _pairs.end(); it++) {
		std::cout << it->first << " " << it->second << " " << std::endl;
	}
	std::cout << std::endl;
	insertShortest();
		std::cout << "after:" << std::endl;
	for (std::list<size_t>::iterator it = _liContainer.begin(); it != _liContainer.end(); it++) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

PmergeMe	PmergeMe::sortContainer() {
	makePairs();
	return *this;
}