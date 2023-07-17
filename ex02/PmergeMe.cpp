#include "PmergeMe.hpp"

bool isNumber(std::string numStr)
{
    bool dot = false;
    for (size_t i = 0; i < numStr.size(); ++i) {
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

double PmergeMe::getElementByIndex(std::list<double>::iterator it, size_t index) {

    //std::list<double>::iterator it = _output.begin();
    std::advance(it, index);
    return *it;
}

std::list<double>::iterator PmergeMe::getIteratorByIndex(std::list<double>::iterator it, size_t index) {

    //std::list<double>::iterator it = _output.begin();
    std::advance(it, index);
    return it;
}

size_t PmergeMe::getNextJacobsthalNum(size_t iterCount, size_t currentNum) {
    return (pow(2, iterCount) - currentNum);
}

//List
void PmergeMe::splitIntoPairsLst() {
    size_t counter = 0;
    std::pair<double, double> arr;
    for (inpIterLst it = _inputLst.begin(); it != _inputLst.end(); ++it) {
        //std::cout << "-" << *it << "-" << std::endl;
        if (!isNumber(*it)) {
            std::cout << "Error" << std::endl;
            exit(0);
        }
		if (counter == 0)
        	arr.first = atof((*it).c_str());
		else if (counter == 1)
			arr.second = atof((*it).c_str());
        if (++counter == 2) {
            this->_pairsLst.push_back(arr);
            counter = 0;
        }
    }
    if (counter == 1) {
        this->_straddler = arr.first;
    }
}

void PmergeMe::sortPairsLst() {
    double tmp;

    for (pairsIter it = _pairsLst.begin(); it != _pairsLst.end(); ++it) {
        if ((*it).first > (*it).second) {
            tmp = (*it).first;
            (*it).first = (*it).second;
            (*it).second = tmp;

        }
    }
}


void PmergeMe::insertionSortPairsLst() {
    double rightMostValue;
    pairsIter nextIter;
    std::pair<double, double> toBeInserted;

	if (_pairsLst.size() == 0)
		return;
    for (pairsIter leftIter = _pairsLst.begin(); leftIter != std::prev(_pairsLst.end()); ++leftIter) {
        nextIter =  std::next(leftIter);
        rightMostValue = (*leftIter).second;
        toBeInserted = *std::next(leftIter);
        if (rightMostValue > toBeInserted.second) {
            for (pairsIter rightIter = nextIter; rightIter != _pairsLst.begin(); --rightIter) {
                rightMostValue = (*std::prev(rightIter)).second;
                if (rightMostValue > toBeInserted.second) {
                    std::iter_swap(std::prev(rightIter), rightIter);
                }
            }
        }
    }
}

void PmergeMe::insertPendNumLst(size_t tagNum, size_t insertionCounter)
{
    size_t index = tagNum - 1;
    double pendValue = this->getElementByIndex(_pendLst.begin(), index);
	int m;
	int low = 0;
    int high = index + insertionCounter;
    if (index == 0) {
        _outputLst.push_front(pendValue);
    } else {
        double outputValue;
        std::list<double>::iterator outputIter;
		while (low <= high) {
            m = low + (high - low) / 2;
			outputValue = this->getElementByIndex(_outputLst.begin(), m);
            if (pendValue == outputValue)
                break;
            else if (low == high && pendValue > outputValue) {
                m += 1;
                break;
            }
			else if (pendValue < outputValue) {
				high = m - 1;
			}
			else if (pendValue > outputValue) {
				low = m + 1;
			}
		}
        outputIter = this->getIteratorByIndex(_outputLst.begin(), m);
        _outputLst.insert(outputIter, pendValue); 
    }
}

void PmergeMe::finalSortLst() {
    for (pairsIter it = _pairsLst.begin(); it != _pairsLst.end(); ++it) {
        _outputLst.push_back((*it).second);
        _pendLst.push_back((*it).first);
    }
    if (this->_size % 2 != 0)
        _pendLst.push_back(this->_straddler);
    size_t jacobsthal = 0;
    size_t prevJacobstahl = 0;
    size_t iterationCounter = 1;
    for (size_t i = 0; i < _pendLst.size() + 2; ++i) {
        prevJacobstahl = jacobsthal;
        jacobsthal = this->getNextJacobsthalNum(i, jacobsthal);
        if (prevJacobstahl == 0)
            continue;
        if (jacobsthal == 1 && prevJacobstahl == 1)
            this->insertPendNumLst(1, iterationCounter);
        if (jacobsthal > _pendLst.size())
            jacobsthal = _pendLst.size();
        for (size_t j = jacobsthal; j > prevJacobstahl; --j) {
            this->insertPendNumLst(j, iterationCounter);
            iterationCounter++;
        }
        if (jacobsthal == _pendLst.size())
            break;
    }
}

void PmergeMe::printResultLst() {
    /*std::cout << "Before:";
    for (std::list<std::string>::iterator it = _inputLst.begin(); it != _inputLst.end(); ++it) {
        std::cout << " " << *it;
    }
    std::cout << std::endl;
    std::cout << "After:";
    for (std::list<double>::iterator it = _outputLst.begin(); it != _outputLst.end(); ++it) {
        std::cout << " " << *it;
    }
    std::cout << std::endl;*/
    double time = (double)this->_timeNeeded / 1000; // / 1000000.0;
    std::cout << "Time to process range of " << this->_size << " elements with std::list needed " << std::fixed << std::setprecision(7) << time << " ms" << std::endl;

}

void PmergeMe::sortLst(char **argv) {
    this->initDataLst(argv);
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
    size_t counter = 0;
    std::pair<double, double> arr;
    for (inpIter it = _inputVec.begin(); it != _inputVec.end(); ++it) {
        //std::cout << "-" << *it << "-" << std::endl;
        if (!isNumber(*it)) {
            std::cout << "Error" << std::endl;
            exit(0);
        }
		if (counter == 0)
			arr.first = atof((*it).c_str());
		else if (counter == 1)
    		arr.second = atof((*it).c_str());
        if (it + 1 == _inputVec.end() && counter == 0) {
            this->_straddler = arr.first;
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
        if ((*it).first > (*it).second) {
            tmp = (*it).first;
            (*it).first = (*it).second;
            (*it).second = tmp;

        }
    }
}


void PmergeMe::insertionSortPairsVec() {
    double rightMostValue;
    pairsIterVec nextIter;
    std::pair<double, double> toBeInserted;

	if (_pairsVec.size() == 0)
		return;
    for (pairsIterVec leftIter = _pairsVec.begin(); leftIter != std::prev(_pairsVec.end()); ++leftIter) {
        nextIter =  std::next(leftIter);
        rightMostValue = (*leftIter).second;
        toBeInserted = *std::next(leftIter);
        if (rightMostValue > toBeInserted.second) {
            for (pairsIterVec rightIter = nextIter; rightIter != _pairsVec.begin(); --rightIter) {
                rightMostValue = (*std::prev(rightIter)).second;
                if (rightMostValue > toBeInserted.second) {
                    std::iter_swap(std::prev(rightIter), rightIter);
                }
            }
        }
    }
}

void PmergeMe::insertPendNumVec(size_t tagNum, size_t insertionCounter)
{
    size_t index = tagNum - 1;
    double pendValue = _pendVec[index];
	int m;
	int low = 0;
    int high = index + insertionCounter;
    if (index == 0) {
        _outputVec.insert(_outputVec.begin(), pendValue);
    } else {
        double outputValue;
        std::vector<double>::iterator outputIter;
		while (low <= high) {
            m = low + (high - low) / 2;
			outputValue = _outputVec[m];
            if (pendValue == outputValue)
                break;
            else if (low == high && pendValue > outputValue) {
                m += 1;
                break;
            }
			else if (pendValue < outputValue) {
				high = m - 1;
			}
			else if (pendValue > outputValue) {
				low = m + 1;
			}
		}
		if (m < _outputVec.size()) {
        	outputIter = _outputVec.begin() + m;
        	_outputVec.insert(outputIter, pendValue);
		} else {
			_outputVec.push_back(pendValue);
		}
    }
}

void PmergeMe::finalSortVec() {
    for (pairsIterVec it = _pairsVec.begin(); it != _pairsVec.end(); ++it) {
        _outputVec.push_back((*it).second);
        _pendVec.push_back((*it).first);
    }
    if (this->_size % 2 != 0)
        _pendVec.push_back(this->_straddler);
    size_t jacobsthal = 0;
    size_t prevJacobstahl = 0;
    size_t insertionCounter = 1;
    for (size_t i = 0; i < _pendVec.size() + 2; ++i) {
        prevJacobstahl = jacobsthal;
        jacobsthal = this->getNextJacobsthalNum(i, jacobsthal);
        if (prevJacobstahl == 0)
            continue;
        if (jacobsthal == 1 && prevJacobstahl == 1)
            this->insertPendNumVec(1, insertionCounter);
        if (jacobsthal > _pendVec.size())
            jacobsthal = _pendVec.size();
        for (size_t j = jacobsthal; j > prevJacobstahl; --j) {
            this->insertPendNumVec(j, insertionCounter);
            insertionCounter++;
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
    double time = (double)this->_timeNeeded / 1000;// / 1000000.0;
    std::cout << "Time to process range of " << this->_size << " elements with std::vector needed " << std::fixed << std::setprecision(7) << time << " ms" << std::endl;
}

void PmergeMe::sortVec(char **argv) {
    this->initDataVec(argv);
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
    for (std::vector<std::string>::iterator it = _inputVec.begin(); it != _inputVec.end(); ++it) {
        std::cout << " " << *it;
    }
    std::cout << std::endl;
    std::cout << "After:";
    for (std::vector<double>::iterator it = _outputVec.begin(); it != _outputVec.end(); ++it) {
        std::cout << " " <<  *it;
    }
    std::cout << std::endl;
}
void PmergeMe::sort(char **argv) {
    //std::streamsize ss = std::cout.precision();
    this->_begin = get_current_microsec();
    this->sortLst(argv);
    this->_end = get_current_microsec();
    this->_timeNeeded = this->_end - this->_begin;
    this->printResultLst();

    this->_begin = get_current_microsec();
    this->sortVec(argv);
    this->_end = get_current_microsec();
    this->_timeNeeded = this->_end - this->_begin;
    this->printResultVec();

    //std::cout.precision(ss);
    std::cout.unsetf(std::ios::fixed);
    std::cout << std::setprecision(-1);
    this->printResult();
}

void PmergeMe::initDataVec(char **argv) {
    std::string input;
    while (*argv) {
        input.append(*argv);
        this->_inputVec.push_back(input);
        input = "\0";
        ++argv;
    }
    this->_size = this->_inputVec.size();
}

void PmergeMe::initDataLst(char **argv) {
    std::string input;
    while (*argv) {
        input.append(*argv);
        this->_inputLst.push_back(input);
        input = "\0";
        ++argv;
    }
    this->_size = this->_inputLst.size();
}

//canonical

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