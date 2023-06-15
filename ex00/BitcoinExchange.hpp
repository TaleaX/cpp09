#ifndef __BITEXCHANGE__
# define __BITEXHCHANGE__
# include <map>
# include <string>
# include <iostream>
# include <fstream>
# include <sstream>
# include <algorithm>

class BitcoinExchange
{
    public:
        class BadInput : public std::exception {
            public:
                virtual std::string what(std::string line) const throw() {
                    return ("Error: bad input => " + line);
                }
        };
        class NegativeNumber : public std::exception {
            public:
                virtual const char* what() const throw() {
                    return ("Error: not a positive number.");
                }
        };
        class Overflow : public std::exception {
            public:
                virtual const char* what() const throw() {
                    return ("Error: too large a number.");
                }
        };
        void readInputFile(std::string inpFile);
        BitcoinExchange& operator=(const BitcoinExchange& rhs);
        BitcoinExchange(const BitcoinExchange& src);
        BitcoinExchange();
        ~BitcoinExchange(){}
    private:
        bool isCorrectDateFormate(int iterCounter, std::string val);
        int getDateId(std::string str);
        void printOutput(std::string date, double amount, double exchangeRate);
        std::map<int, double> _database;

};

#endif