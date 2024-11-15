#ifndef BITCOIN_EXCHANGE_HPP
#define BITCOIN_EXCHANGE_HPP

#define DATA_FORMAT_ERR "ERR: Bad data.csv file format"
#define INPUT_FORMAT_ERR "ERR: Bad input file format"
#define DATA_FILE_ERR "ERR: File data.csv not found or not readable"
#define INPUT_FILE_ERR "ERR: Input file not found or not readable"
#define DATA_LINE_TOO_SHORT_ERR "ERR: data.csv file lines need at least 12 characters"
#define INPUT_LINE_TOO_SHORT_ERR "ERR: Input file lines need at least 12 characters"
#define DATA_DATE_FORMAT_ERR "ERR: Bad data.csv file date format (expected: YYYY-MM-DD,X...)"
#define INPUT_DATE_FORMAT_ERR "ERR: Bad input file date format (expected: YYYY-MM-DD,X...)"
#define IMP_DATA_DATE_ERR "ERR: This data date is impossible"
#define IMP_INPUT_DATE_ERR "ERR: This input date is impossible"
#define DATA_VALUE_ERR "ERR: Bad data value"
#define INPUT_VALUE_ERR "ERR: Bad input value"
#define DATA_DATE_ALREADY_ERR "Error: Data date already exist"

#include <iostream>
#include <fstream>
#include <string>
#include <map>

#include <stdexcept>
#include <cstdlib>


class BitcoinExchange {
	private:
		typedef std::map<size_t, double>::const_iterator iterator;
		BitcoinExchange() {}
		BitcoinExchange(const BitcoinExchange& copy);
		size_t	get_total_days(size_t year, size_t month, size_t day) const;
		void	readDataFile();
		void 	readInputFile();
		void	parseDataFile(std::ifstream &file);
		void	parseInputFile(std::ifstream &file);
		void	howMuch(size_t days_since_baby_jesus_birth, double quantity, size_t year, size_t month, size_t day) const;
		std::string					_fileName;
		std::map<size_t, double>	_map;
	public:
		BitcoinExchange &operator=(const BitcoinExchange &other);
		BitcoinExchange(std::string file);
		~BitcoinExchange() {};
};
#endif