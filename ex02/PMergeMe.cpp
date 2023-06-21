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

double PMergeMe::getElementByIndex(int index) {

    std::list<double>::iterator it = _output.begin();
    std::advance(it, index);
    return *it;
}

std::list<double>::iterator PMergeMe::getIteratorByIndex(int index) {

    std::list<double>::iterator it = _output.begin();
    std::advance(it, index);
    return it;
}

int PMergeMe::getNextJacobsthalNum(int iterCount, int currentNum) {
    return (pow(2, iterCount) - currentNum);
}

void PMergeMe::splitIntoPairs() {
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
            counter = 0;
        }
    }
}

void PMergeMe::sortPairs() {
    double tmp;

    for (pairsIter it = _pairs.begin(); it != _pairs.end(); ++it) {
        if ((*it)[0] > (*it)[1]) {
            tmp = (*it)[0];
            (*it)[0] = (*it)[1];
            (*it)[1] = tmp;

        }
    }
}


void PMergeMe::insertionSortPairs() {
    double rightMostValue;
    pairsIter nextIter;
    std::array<double, 2> toBeInserted;

    for (pairsIter leftIter = _pairs.begin(); leftIter != std::prev(_pairs.end()); ++leftIter) {
        nextIter =  std::next(leftIter);
        rightMostValue = (*leftIter)[1];
        toBeInserted = *std::next(leftIter);
        if (rightMostValue > toBeInserted[1]) {
            for (pairsIter rightIter = nextIter; rightIter != _pairs.begin(); --rightIter) {
                rightMostValue = (*std::prev(rightIter))[1];
                if (rightMostValue > toBeInserted[1]) {
                    std::iter_swap(std::prev(rightIter), rightIter);
                }
            }
        }
    }
}

void PMergeMe::insertPendNum(int tagNum)
{
    int index = tagNum - 1;
    int minIndex = index - 2;
   // std::cout << "index: " << index << std::endl;
    if (index == 0) {
        _output.push_front(_pend[index]);
    } else {
       /*  std::cout << "index: " << index << std::endl;
        std::cout << "pend 0: " << _pend[0] << std::endl;
        std::cout << "pend: " << _pend[index] << std::endl; */
        for (int i = minIndex; i <= index; ++i) {
            double outputValue = this->getElementByIndex(i);
            std::list<double>::iterator outputIter = this->getIteratorByIndex(i);
            if (_pend[index] <= outputValue) {
                _output.insert(outputIter, _pend[index]);
                break;
            }
        }
    }
}


void PMergeMe::finalSort() {
    int jacobsthal = 0;
    int prevJacobstahl = 0;
    for (int i = 0; i < _pend.size() + 2; ++i) {
        prevJacobstahl = jacobsthal;
        jacobsthal = this->getNextJacobsthalNum(i, jacobsthal);
        std::cout << "i: " << i << "jacob: " << jacobsthal << std::endl;
        if (prevJacobstahl == 0)
            continue;
        if (jacobsthal == 1 && prevJacobstahl == 1)
            this->insertPendNum(1);
        if (jacobsthal > _pend.size())
            jacobsthal = _pend.size();
        for (int j = jacobsthal; j > prevJacobstahl; --j) {
            std::cout << "j: " << j << std::endl;
            this->insertPendNum(j);
        }
        if (jacobsthal == _pend.size())
            break;
    }
}

void PMergeMe::sort() {
    this->splitIntoPairs();
    this->sortPairs();
    this->insertionSortPairs();
    this->finalSort();
    for (pairsIter it = _pairs.begin(); it != _pairs.end(); ++it) {
        std::cout << (*it)[0] << " " << (*it)[1] << std::endl;
    }
    for (std::list<double>::iterator it = _output.begin(); it != _output.end(); ++it) {
        std::cout << *it << std::endl;
    } 
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
    
    
    /*if (_size % 2 != 0)
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