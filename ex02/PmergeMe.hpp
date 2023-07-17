#ifndef __PMERGEME__
# define __PMERGEME__

# include <list>
# include <vector>
# include <array>
# include <iostream>
# include <sstream>
# include <cmath>
# include <sys/time.h>
#include <iomanip>
#include <cstdint>

typedef std::list< std::pair<double, double> >::iterator pairsIter;
typedef std::vector< std::pair<double, double> >::iterator pairsIterVec;
typedef std::vector<std::string>::iterator inpIter;
typedef std::list<std::string>::iterator inpIterLst;
typedef std::string::iterator strIter;

class PmergeMe
{
    public:
        void sort(char **argv);
        PmergeMe& operator=(const PmergeMe& rhs);
        PmergeMe(const PmergeMe& src);
        PmergeMe(){}
        ~PmergeMe(){}
    private:
        //List
        void splitIntoPairsLst();
        void sortPairsLst();
        void insertionSortPairsLst();
        void finalSortLst();
        void insertPendNumLst(size_t tagNum, size_t insertionCounter);
        void printResultLst();
        void sortLst(char **argv);
        void initDataLst(char **argv);

        //Vector
        void splitIntoPairsVec();
        void sortPairsVec();
        void insertionSortPairsVec();
        void finalSortVec();
        void insertPendNumVec(size_t tagNum, size_t insertionCounter);
        void printResultVec();
        void sortVec(char **argv);
        void initDataVec(char **argv);

        void printResult();
        double getElementByIndex(std::list<double>::iterator it, size_t index);
        size_t getNextJacobsthalNum(size_t iterCount, size_t currentNum);
        std::list<double>::iterator getIteratorByIndex(std::list<double>::iterator it, size_t index);

        size_t _size;
        double  _straddler;
        uint64_t _begin;
        uint64_t _end;
        uint64_t _timeNeeded;

        //List
        std::list<std::string> _inputLst;
        std::list< std::pair<double, double> > _pairsLst;
        std::list<double> _outputLst;
        std::list<double> _pendLst;

        //Vector
        std::vector<std::string> _inputVec;
        std::vector< std::pair<double, double> > _pairsVec;
        std::vector<double> _outputVec;
        std::vector<double> _pendVec;
};

#endif