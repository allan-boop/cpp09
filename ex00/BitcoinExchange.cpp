#include "BitcoinExchange.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <map>

#include <stdexcept>
#include <cstdlib>

void errManager(size_t lineCounter, std::string errType) {
	std::cerr << "Line " << lineCounter << ": ";
	throw std::runtime_error(errType);
}

BitcoinExchange::BitcoinExchange(std::string file) : _fileName(file) {
	readDataFile();
	readInputFile();
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
	_fileName = other._fileName;
	return *this;
}

void	BitcoinExchange::readDataFile() {
	std::ifstream file("data.csv");
	if (!file.is_open())
		throw std::runtime_error(DATA_FILE_ERR);
	parseDataFile(file);
}

void	BitcoinExchange::parseDataFile(std::ifstream &file) {
	bool		isFirstLine = true;
	std::string	line;
	size_t		lineCounter = 0;
	size_t		month_days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30};

	while (std::getline(file, line))
	{
		lineCounter++;
		if (isFirstLine)
		{
			isFirstLine = false;
			if (line != "date,exchange_rate")
				errManager(lineCounter, DATA_FORMAT_ERR);
			continue;
		}
		size_t	year = 0;
		size_t	month = 0;
		size_t	day = 0;
		if (line.length() < 12)
			errManager(lineCounter, DATA_LINE_TOO_SHORT_ERR);
		bool dot = false;
		for (size_t i = 0; i < line.length(); i++)
		{
			if (i < 10 && i != 4 && i != 7 && !isdigit(line[i]))
				errManager(lineCounter, DATA_DATE_FORMAT_ERR);
			if (i == 4 || i == 7) {
				if (line[i] != '-')
					errManager(lineCounter, DATA_DATE_FORMAT_ERR);
			} else if (i < 4) {
				year = year * 10 + line[i] - '0';
			} else if (i < 7) {
				month = month * 10 + line[i] - '0';
			} else if (i < 10) {
				day = day * 10 + line[i] - '0';
			} else if (i == 10 && line[i] != ',') {
				errManager(lineCounter, DATA_DATE_FORMAT_ERR);
			} else if (i > 10) {
				if (line[i] == '.') {
					if (dot == true || i == 11)
						errManager(lineCounter, DATA_VALUE_ERR);
					dot = true;
				} else if (!isdigit(line[i]))
					errManager(lineCounter, DATA_VALUE_ERR);
			}
		}
		if (year > 2024 || month > 12 || month < 1 || day > month_days[month -1] || day < 1 || (month == 2 && day == 29 && ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)))
			errManager(lineCounter, IMP_DATA_DATE_ERR);
		size_t nbOfDay = get_total_days(year, month, day);
		if (_map.find(nbOfDay) == _map.end())
			_map[nbOfDay] = std::atof(&(line.c_str())[11]);
		else
			errManager(lineCounter, DATA_DATE_ALREADY_ERR);
	}
}

size_t BitcoinExchange::get_total_days(size_t year, size_t month, size_t day) const
{
	size_t	total_days = day;
	size_t	month_days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30};

	for (size_t i = 0; i < month - 1; i++)
	{
		total_days += month_days[i];
	}
	if (((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) && month > 2)
		total_days++;
	total_days += year * 365;
	if (year > 0) {
		total_days += ((year - 1) / 4) - (((year - 1) / 100) + ((year - 1) / 400));
	}
	return total_days;
}

void	BitcoinExchange::readInputFile() {
	std::ifstream file(_fileName.c_str());
	if (!file.is_open())
		throw std::runtime_error(INPUT_FILE_ERR);
	parseInputFile(file);
}

void	BitcoinExchange::parseInputFile(std::ifstream &file) {
	bool		isFirstLine = true;
	std::string	line;
	size_t		lineCounter = 0;
	size_t		month_days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30};

	while (std::getline(file, line))
	{
		lineCounter++;
		if (isFirstLine)
		{
			isFirstLine = false;
			if (line != "date | value")
				throw std::runtime_error(INPUT_FORMAT_ERR);
			continue;
		}
		size_t	year = 0;
		size_t	month = 0;
		size_t	day = 0;
		if (line.length() < 14) {
			std::cerr << INPUT_LINE_TOO_SHORT_ERR << std::endl;
			continue;
		}
		bool dot = false;
		for (size_t i = 0; i < line.length(); i++)
		{
			if (i < 10 && i != 4 && i != 7 && !isdigit(line[i])) {
				std::cerr << INPUT_DATE_FORMAT_ERR << std::endl;
				continue;
			}
			if (i == 4 || i == 7) {
				if (line[i] != '-') {
					std::cerr << INPUT_DATE_FORMAT_ERR << std::endl;
					continue;
				}
			} else if (i < 4) {
				year = year * 10 + line[i] - '0';
			} else if (i < 7) {
				month = month * 10 + line[i] - '0';
			} else if (i < 10) {
				day = day * 10 + line[i] - '0';
			} else if (i == 10 && (line[i] != ' ' || line[i + 1] != '|' || line[i + 2] !=  ' ')) {
				std::cerr << INPUT_DATE_FORMAT_ERR << std::endl;
				continue;
			} else if (i >= 13) {
				if (line[i] == '.') {
					if (dot == true || i == 13)
					{
						std::cerr << INPUT_VALUE_ERR << std::endl;
						continue;
					}
					dot = true;
				} else if (!isdigit(line[i]))
				{
					std::cerr << INPUT_VALUE_ERR << std::endl;
					continue;
				}
			}
		}
		if (year > 2024 || month > 12 || month < 1 || day > month_days[month -1] || day < 1 || (month == 2 && day == 29 && ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)))
		{
			std::cerr << IMP_INPUT_DATE_ERR << std::endl;
			continue;
		}
		double	qtt = std::atof(&(line.c_str())[13]);
		if (qtt < 0 || qtt > 1000)
		{
			std::cerr << INPUT_VALUE_ERR << std::endl;
			continue;
		}
		size_t total_days = get_total_days(year, month, day);
		howMuch(total_days, qtt, year, month, day);
	}
}
void	BitcoinExchange::howMuch(size_t days_since_baby_jesus_birth, double quantity, size_t year, size_t month, size_t day) const
{
	bool done = false;
	for (iterator it = _map.begin(); it != _map.end(); it++)
	{
		if (it->first == days_since_baby_jesus_birth)
		{
			std::cout << year << "-" << ((month < 10) ? "0" : "") << month << "-" << ((day < 10) ? "0" : "") << day << "=> " << quantity << " => " << (it->second * quantity) << std::endl;
			done = true;
			break;
		}
		if (it->first > days_since_baby_jesus_birth)
		{
			if (it == _map.begin())
				break;
			it--;
			std::cout << year << "-" << ((month < 10) ? "0" : "") << month << "-" << ((day < 10) ? "0" : "") << day << "=> " << quantity << " => " << (it->second * quantity) << std::endl;
			done = true;
			break;
		}
	}
	if (!done)
	{
		std::cout << year << "-" << ((month < 10) ? "0" : "") << month << "-" << ((day < 10) ? "0" : "") << day << ": No data available" << std::endl;
	}
}