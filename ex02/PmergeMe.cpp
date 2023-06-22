#include "PmergeMe.hpp"

bool isNumber(std::string numStr)
{
    bool dot = false;
    for (int i = 0; i < numStr.size(); ++i) {
        if (i == 0 && numStr[i] == '-' && numStr.size() > 1)
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

uint64_t	get_current_microsec(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000000 + time.tv_usec);
}

double PmergeMe::getElementByIndex(std::list<double>::iterator it, int index) {

    //std::list<double>::iterator it = _output.begin();
    std::advance(it, index);
    return *it;
}

std::list<double>::iterator PmergeMe::getIteratorByIndex(std::list<double>::iterator it, int index) {

    //std::list<double>::iterator it = _output.begin();
    std::advance(it, index);
    return it;
}

int PmergeMe::getNextJacobsthalNum(int iterCount, int currentNum) {
    return (pow(2, iterCount) - currentNum);
}

//List
void PmergeMe::splitIntoPairsLst() {
    int counter = 0;
    std::array<double, 2> arr;
    for (inpIter it = _input.begin(); it != _input.end(); ++it) {
        //std::cout << "-" << *it << "-" << std::endl;
        if (!isNumber(*it)) {
            std::cout << "Error" << std::endl;
            exit(0);
        }
        arr[counter] = atof((*it).c_str());
        if (it + 1 == _input.end() && counter == 0) {
            this->_straddler = arr[counter];
        }
        if (++counter == 2) {
            this->_pairsLst.push_back(arr);
            counter = 0;
        }
    }
}

void PmergeMe::sortPairsLst() {
    double tmp;

    for (pairsIter it = _pairsLst.begin(); it != _pairsLst.end(); ++it) {
        if ((*it)[0] > (*it)[1]) {
            tmp = (*it)[0];
            (*it)[0] = (*it)[1];
            (*it)[1] = tmp;

        }
    }
}


void PmergeMe::insertionSortPairsLst() {
    double rightMostValue;
    pairsIter nextIter;
    std::array<double, 2> toBeInserted;

    for (pairsIter leftIter = _pairsLst.begin(); leftIter != std::prev(_pairsLst.end()); ++leftIter) {
        nextIter =  std::next(leftIter);
        rightMostValue = (*leftIter)[1];
        toBeInserted = *std::next(leftIter);
        if (rightMostValue > toBeInserted[1]) {
            for (pairsIter rightIter = nextIter; rightIter != _pairsLst.begin(); --rightIter) {
                rightMostValue = (*std::prev(rightIter))[1];
                if (rightMostValue > toBeInserted[1]) {
                    std::iter_swap(std::prev(rightIter), rightIter);
                }
            }
        }
    }
}

void PmergeMe::insertPendNumLst(int tagNum)
{
    int index = tagNum - 1;
    double pendValue = this->getElementByIndex(_pendLst.begin(), index);
    if (index == 0) {
        _outputLst.push_front(pendValue);
    } else {
        double outputValue;
        std::list<double>::iterator outputIter;
        for (int i = 0; i <= index; ++i) {
            outputValue = this->getElementByIndex(_outputLst.begin(), i);
            outputIter = this->getIteratorByIndex(_outputLst.begin(), i);
            if (pendValue <= outputValue) {
                _outputLst.insert(outputIter, pendValue);
                break;
            }
        }
    }
}


void PmergeMe::finalSortLst() {
    for (pairsIter it = _pairsLst.begin(); it != _pairsLst.end(); ++it) {
        _outputLst.push_back((*it)[1]);
        _pendLst.push_back((*it)[0]);
    }
    if (this->_size % 2 != 0)
        _pendLst.push_back(this->_straddler);
    int jacobsthal = 0;
    int prevJacobstahl = 0;
    for (int i = 0; i < _pendLst.size() + 2; ++i) {
        prevJacobstahl = jacobsthal;
        jacobsthal = this->getNextJacobsthalNum(i, jacobsthal);
        if (prevJacobstahl == 0)
            continue;
        if (jacobsthal == 1 && prevJacobstahl == 1)
            this->insertPendNumLst(1);
        if (jacobsthal > _pendLst.size())
            jacobsthal = _pendLst.size();
        for (int j = jacobsthal; j > prevJacobstahl; --j) {
            this->insertPendNumLst(j);
        }
        if (jacobsthal == _pendLst.size())
            break;
    }
}

void PmergeMe::printResultLst() {
    /* std::cout << "Before:";
    for (std::vector<std::string>::iterator it = _input.begin(); it != _input.end(); ++it) {
        std::cout << " " << *it;
    }
    std::cout << std::endl;
    std::cout << "After:";
    for (std::list<double>::iterator it = _outputLst.begin(); it != _outputLst.end(); ++it) {
        std::cout << " " << *it;
    }
    std::cout << std::endl; */
    double time = (double)this->_timeNeeded / 1000000.0;
    std::cout << "Time to process range of " << this->_size << " elements with std::list needed " << std::fixed << std::setprecision(7) << time << " us" << std::endl;

}

void PmergeMe::sortLst() {
    this->splitIntoPairsLst();
    this->sortPairsLst();
    this->insertionSortPairsLst();
    this->finalSortLst();
   /*  for (pairsIter it = _pairs.begin(); it != _pairs.end(); ++it) {
        std::cout << (*it)[0] << " " << (*it)[1] << std::endl;
    } */
}




//Vec
void PmergeMe::splitIntoPairsVec() {
    int counter = 0;
    std::array<double, 2> arr;
    for (inpIter it = _input.begin(); it != _input.end(); ++it) {
        //std::cout << "-" << *it << "-" << std::endl;
        if (!isNumber(*it)) {
            std::cout << "Error" << std::endl;
            exit(0);
        }
        arr[counter] = atof((*it).c_str());
        if (it + 1 == _input.end() && counter == 0) {
            this->_straddler = arr[counter];
        }
        if (++counter == 2) {
            this->_pairsVec.push_back(arr);
            counter = 0;
        }
    }
}

void PmergeMe::sortPairsVec() {
    double tmp;

    for (pairsIterVec it = _pairsVec.begin(); it != _pairsVec.end(); ++it) {
        if ((*it)[0] > (*it)[1]) {
            tmp = (*it)[0];
            (*it)[0] = (*it)[1];
            (*it)[1] = tmp;

        }
    }
}


void PmergeMe::insertionSortPairsVec() {
    double rightMostValue;
    pairsIterVec nextIter;
    std::array<double, 2> toBeInserted;

    for (pairsIterVec leftIter = _pairsVec.begin(); leftIter != std::prev(_pairsVec.end()); ++leftIter) {
        nextIter =  std::next(leftIter);
        rightMostValue = (*leftIter)[1];
        toBeInserted = *std::next(leftIter);
        if (rightMostValue > toBeInserted[1]) {
            for (pairsIterVec rightIter = nextIter; rightIter != _pairsVec.begin(); --rightIter) {
                rightMostValue = (*std::prev(rightIter))[1];
                if (rightMostValue > toBeInserted[1]) {
                    std::iter_swap(std::prev(rightIter), rightIter);
                }
            }
        }
    }
}

void PmergeMe::insertPendNumVec(int tagNum)
{
    int index = tagNum - 1;
    double pendValue = _pendVec[index];
    if (index == 0) {
        _outputVec.insert(_outputVec.begin(), pendValue);
    } else {
        double outputValue;
        std::vector<double>::iterator outputIter;
        for (int i = 0; i <= index; ++i) {
            outputValue = _outputVec[i];
            outputIter = _outputVec.begin() + i;
            //outputValue = this->getElementByIndex(_outputVec.begin(), i);
            //outputIter = this->getIteratorByIndex(_outputVec.begin(), i);
            if (pendValue <= outputValue) {
                _outputVec.insert(outputIter, pendValue);
                break;
            }
        }
    }
}


void PmergeMe::finalSortVec() {
    for (pairsIterVec it = _pairsVec.begin(); it != _pairsVec.end(); ++it) {
        _outputVec.push_back((*it)[1]);
        _pendVec.push_back((*it)[0]);
    }
    if (this->_size % 2 != 0)
        _pendVec.push_back(this->_straddler);
    int jacobsthal = 0;
    int prevJacobstahl = 0;
    for (int i = 0; i < _pendVec.size() + 2; ++i) {
        prevJacobstahl = jacobsthal;
        jacobsthal = this->getNextJacobsthalNum(i, jacobsthal);
        if (prevJacobstahl == 0)
            continue;
        if (jacobsthal == 1 && prevJacobstahl == 1)
            this->insertPendNumVec(1);
        if (jacobsthal > _pendVec.size())
            jacobsthal = _pendVec.size();
        for (int j = jacobsthal; j > prevJacobstahl; --j) {
            this->insertPendNumVec(j);
        }
        if (jacobsthal == _pendVec.size())
            break;
    }
}

void PmergeMe::printResultVec() {
   /*  std::cout << "Before:";
    for (std::vector<std::string>::iterator it = _input.begin(); it != _input.end(); ++it) {
        std::cout << " " << *it;
    }
    std::cout << std::endl;
    std::cout << "After:";
    for (std::vector<double>::iterator it = _outputVec.begin(); it != _outputVec.end(); ++it) {
        std::cout << " " << *it;
    }
    std::cout << std::endl; */
    double time = (double)this->_timeNeeded / 1000000.0;
    std::cout << "Time to process range of " << this->_size << " elements with std::vector needed " << std::fixed << std::setprecision(7) << time << " us" << std::endl;
}

void PmergeMe::sortVec() {
    this->splitIntoPairsVec();
    this->sortPairsVec();
    this->insertionSortPairsVec();
    this->finalSortVec();
   /*  for (pairsIter it = _pairs.begin(); it != _pairs.end(); ++it) {
        std::cout << (*it)[0] << " " << (*it)[1] << std::endl;
    } */
}

void PmergeMe::printResult() {
    std::cout << "Before:";
    for (std::vector<std::string>::iterator it = _input.begin(); it != _input.end(); ++it) {
        std::cout << " " << *it;
    }
    std::cout << std::endl;
    std::cout << "After:";
    for (std::vector<double>::iterator it = _outputVec.begin(); it != _outputVec.end(); ++it) {
        std::cout << " " <<  *it;
    }
    std::cout << std::endl;
}
void PmergeMe::sort() {
    //std::streamsize ss = std::cout.precision();
    this->_begin = get_current_microsec();
    this->sortLst();
    this->_end = get_current_microsec();
    this->_timeNeeded = this->_end - this->_begin;
    this->printResultLst();

    this->_begin = get_current_microsec();
    this->sortVec();
    this->_end = get_current_microsec();
    this->_timeNeeded = this->_end - this->_begin;
    this->printResultVec();

    //std::cout.precision(ss);
    std::cout.unsetf(std::ios::fixed);
    std::cout << std::setprecision(-1);
    this->printResult();
}

//canonical
PmergeMe::PmergeMe(char **argv) {
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

PmergeMe::PmergeMe(const PmergeMe& src)
{
    *this = src;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& rhs) 
{
    if (this != &rhs) {
        *this = rhs;
    }
    return *this;
}