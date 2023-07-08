#include "BitcoinExchange.hpp"

//todo string handle wrong input: a in input, input doesnt exist and is the smallest,date doest exist (moth 13, day 45 etc)

// bool BitcoinExchange::isCorrectDateFormate(int iterCounter, std::string val)
// {
//     if (iterCounter == 0 && val.length() != 4)
//         return false;
//     if ((iterCounter == 1 || iterCounter == 2) && val.length() != 2)
//         return false;
//     return true;
// }

bool isIntNumber(std::string numStr)
{
    for (size_t i = 0; i < numStr.size(); ++i) {
        if (!isdigit(numStr[i]))
            return false;
    }
    return true;
}

bool BitcoinExchange::isCorrectDateFormate(std::string numStr)
{
	if (numStr.size() != 8)
		return false;
    if (!isIntNumber(numStr))
		return false;
	std::string year = numStr.substr(0,4);
	std::string month = numStr.substr(4, 2);
	std::string day = numStr.substr(6, 2);
	// int yearNum = atoi(year.c_str());
	int monthNum = atoi(month.c_str());
	int dayNum = atoi(day.c_str());
	if (monthNum > 12)
		return false;
	if (monthNum == 2 && dayNum > 28)
		return false;
	if (monthNum % 2 == 0 && monthNum <= 7 && dayNum > 30)
		return false;
	if (monthNum % 2 != 0 && monthNum <= 7 && dayNum > 31)
		return false;
	if (monthNum % 2 == 0 && monthNum > 7 && dayNum > 31)
		return false;
	if (monthNum % 2 != 0 && monthNum > 7 && dayNum > 30)
		return false;
    return true;
}

//priv
int BitcoinExchange::getDateId(std::string str)
{
    std::istringstream iss(str);
    std::string val;
    std::string idStr;// = "00000000";
    int id;
    int iterCounter = 0;
    //size_t nextPos = 0;

    while (getline(iss, val, '-')) {
        // if (!isCorrectDateFormate(iterCounter, val))
        //     return -1;
        /*if (val[0] == '0')
            val.replace(0, 1, "");*/
        idStr += val;
        //idStr.replace(nextPos, val.length(), val);
        //nextPos = nextPos + val.length();
        ++iterCounter;
    }
	if (iterCounter != 3)
		return -1;
	// if (idStr[4] == '0' && idStr[5] == '0')
	// 	idStr[5] = '1';
	// if (idStr[6] == '0' && idStr[7] == '0')
	// 	idStr[7] = '1';
	if (!isCorrectDateFormate(idStr)) {
		return -1;
	}
    id = atoi(idStr.c_str());
    return id;
}

bool isNumber(std::string numStr)
{
    bool dot = false;
    for (size_t i = 0; i < numStr.size(); ++i) {
        if (i == 0 && numStr[i] == '-')
            continue;
        if (!dot && numStr[i] == '.') {
            dot = true;
            continue;
        }
        if (!isdigit(numStr[i]))
            return false;
    }
    return true;
}

double BitcoinExchange::getAmount(std::string amountStr)
{
	double amount;

	if (!isNumber(amountStr)) throw BitcoinExchange::BadInput();

	amount = atof(amountStr.c_str());

	if (amount < 0) throw BitcoinExchange::NegativeNumber();
	if (amount > 1000) throw BitcoinExchange::Overflow();
	return amount;
}

void BitcoinExchange::printOutput(std::string date, double amount, double exchangeRate)
{
    std::cout << date << " => " << amount << " = " << amount * exchangeRate << std::endl;
}

//public
void BitcoinExchange::readInputFile(std::string inp)
{
    std::ifstream inpFile;
    std::string line;
    std::string delim = " | ";
	int id;
	double amount;
	bool firstIter = true;

    inpFile.open(inp);
    if (!inpFile)
        std::cerr << "Error: could not open file" << std::endl;
    else {
        while(std::getline(inpFile, line)) {
            try {
				if (firstIter && line != "date | value") {
					firstIter = false;
					throw BitcoinExchange::BadInput();
				}
				else if (firstIter && line == "date | value") {
					firstIter = false;
					continue;
				}
                size_t delimPos = line.find(delim);
                if (delimPos == std::string::npos) throw BitcoinExchange::BadInput();
                std::string date = line.substr(0, delimPos);
                int countDelim = std::count(date.begin(), date.end(), '-');
                if (countDelim > 2) throw BitcoinExchange::BadInput();
                std::string amountStr = line.substr(delimPos + delim.length());
                id = this->getDateId(date);
				if (id == -1) throw BitcoinExchange::BadInput();
            	amount = this->getAmount(amountStr);
                for (std::map<int,double>::iterator it = this->_database.begin(); it != this->_database.end(); ++it) {
                    if (it->first == id) {
                        this->printOutput(date, amount, it->second);
                        break;
                    } else if (it->first > id) {
						if (it == this->_database.begin()) throw BitcoinExchange::BadInput();
                        --it;
                        this->printOutput(date, amount, it->second);
                        break;
                    }
                }
            } catch (BitcoinExchange::BadInput& e) {
                std::cout << e.what(line) << std::endl;
            } catch (std::exception& e) {
                std::cout << e.what() << std::endl;
            }
        }
    }
    inpFile.close();
}

//canonical
BitcoinExchange::BitcoinExchange()
{
    std::ifstream data;
    std::string line;
    std::string delim = ",";

    data.open("data.csv");
    if (!data)
        std::cerr << "Failed to open the file." << std::endl;
    else {
        while(std::getline(data, line)) {
			try {
				if (line == "date,exchange_rate")
					continue;
				size_t delimPos = line.find(delim);
				if (delimPos == std::string::npos) throw BitcoinExchange::BadInput();
				std::string key = line.substr(0, delimPos);
				std::string value = line.substr(delimPos + delim.length());
				int id = this->getDateId(key);
				if (id == -1) throw BitcoinExchange::BadInput();
				double val = atof(value.c_str());
				if (val < 0) throw BitcoinExchange::NegativeNumber();
				if (val > 2147483647) throw BitcoinExchange::Overflow();
				this->_database[id] = val;

			} catch (BitcoinExchange::BadInput& e) {
                std::cout << e.what(line) << std::endl;
            } catch (std::exception& e) {
                std::cout << e.what() << std::endl;
            }
        }
    }
    data.close();
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& src)
{
    *this = src;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& rhs) 
{
    if (this != &rhs) {
        *this = rhs;
    }
    return *this;
}