#include "BitcoinExchange.hpp"

bool BitcoinExchange::isCorrectDateFormate(int iterCounter, std::string val)
{
    if (iterCounter == 0 && val.length() != 4)
        return false;
    if ((iterCounter == 1 || iterCounter == 2) && val.length() != 2)
        return false;
    return true;
}

//priv
int BitcoinExchange::getDateId(std::string str)
{
    std::istringstream iss(str);
    std::string val;
    std::string idStr = "00000000";
    int id;
    int iterCounter = 0;
    size_t nextPos = 0;

    while (getline(iss, val, '-')) {
        if (!isCorrectDateFormate(iterCounter, val))
            return -1;
        /*if (val[0] == '0')
            val.replace(0, 1, "");*/
        //idStr += val;
        idStr.replace(nextPos, val.length(), val);
        nextPos = nextPos + val.length();
        ++iterCounter;
    }
    id = atoi(idStr.c_str());
    return id;
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

    inpFile.open(inp);
    if (!inpFile)
        std::cerr << "Error: could not open file" << std::endl;
    else {
        while(std::getline(inpFile, line)) {
            if (line == "date | value")
                continue;
            try {
                size_t delimPos = line.find(delim);
                if (delimPos == std::string::npos) throw BitcoinExchange::BadInput();
                std::string date = line.substr(0, delimPos);
                int countDelim = std::count(date.begin(), date.end(), '-');
                if (countDelim > 2) throw BitcoinExchange::BadInput();
                std::string amountStr = line.substr(delimPos + delim.length());
                int id = this->getDateId(date);
                if (id == -1) throw BitcoinExchange::BadInput();
                double amount = atof(amountStr.c_str());
                if (amount < 0) throw BitcoinExchange::NegativeNumber();
                if (amount > 2147483647) throw BitcoinExchange::Overflow();
                for (std::map<int,double>::iterator it = this->_database.begin(); it != this->_database.end(); ++it) {
                    if (it->first == id) {
                        this->printOutput(date, amount, it->second);
                        break;
                    } else if (it->first > id) {
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
            if (line == "date,exchange_rate")
                continue;
            size_t delimPos = line.find(delim);
            if (delimPos == std::string::npos) throw BitcoinExchange::BadInput();
            std::string key = line.substr(0, delimPos);
            std::string value = line.substr(delimPos + delim.length());
            int id = this->getDateId(key);
            double val = atof(value.c_str());
            if (val < 0) throw BitcoinExchange::NegativeNumber();
            if (val > 2147483647) throw BitcoinExchange::Overflow();
            this->_database[id] = val;
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