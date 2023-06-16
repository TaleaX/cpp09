#include "PMergeMe.hpp"

bool isNumber(std::string numStr)
{
    bool dot = false;
    for (int i = 0; i < numStr.size(); ++i) {
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

//canonical
PMergeMe::PMergeMe(char **argv) {
    /*std::stringstream iss(input);
    std::string token;
    while (getline(iss, token, ' ')) {
        this->_input.push_back(token);
    }*/
    std::string input;
    while (*argv) {
        input.append(*argv);
        this->_input.push_back(input);
        input = "\0";
        ++argv;
    }
    this->_size = this->_input.size();
    int counter = 0;
    std::array<double, 2> arr;
    for (inpIter it = _input.begin(); it != _input.end(); ++it) {
        std::cout << "-" << *it << "-" << std::endl;
        if (!isNumber(*it)) {
            std::cout << "Error" << std::endl;
            exit(0);
        }
        arr[counter] = atof((*it).c_str());
        if (it + 1 == _input.end() && counter == 0) {
            this->_straddler = arr[counter];
        }
        if (++counter == 2) {
            this->_pairs.push_back(arr);
            std::cout << "in here" << std::endl;
            counter = 0;
        }
    }
    /*for (pairsIter it = _pairs.begin(); it != _pairs.end(); ++it) {
        std::cout << (*it)[0] << " " << (*it)[1] << std::endl;
    }
    if (_size % 2 != 0)
        std::cout << "straddler: " << _straddler << std::endl;*/
}

PMergeMe::PMergeMe(const PMergeMe& src)
{
    *this = src;
}

PMergeMe& PMergeMe::operator=(const PMergeMe& rhs) 
{
    if (this != &rhs) {
        *this = rhs;
    }
    return *this;
}