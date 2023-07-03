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

typedef std::list< std::array<double, 2> >::iterator pairsIter;
typedef std::vector< std::array<double, 2> >::iterator pairsIterVec;
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
        void insertPendNumLst(int tagNum, int insertionCounter);
        void printResultLst();
        void sortLst(char **argv);
        void initDataLst(char **argv);

        //Vector
        void splitIntoPairsVec();
        void sortPairsVec();
        void insertionSortPairsVec();
        void finalSortVec();
        void insertPendNumVec(int tagNum, int insertionCounter);
        void printResultVec();
        void sortVec(char **argv);
        void initDataVec(char **argv);

        void printResult();
        double getElementByIndex(std::list<double>::iterator it, int index);
        int getNextJacobsthalNum(int iterCount, int currentNum);
        std::list<double>::iterator getIteratorByIndex(std::list<double>::iterator it, int index);

        int _size;
        double  _straddler;
        uint64_t _begin;
        uint64_t _end;
        uint64_t _timeNeeded;

        //List
        std::list<std::string> _inputLst;
        std::list< std::array<double, 2> > _pairsLst;
        std::list<double> _outputLst;
        std::list<double> _pendLst;

        //Vector
        std::vector<std::string> _inputVec;
        std::vector< std::array<double, 2> > _pairsVec;
        std::vector<double> _outputVec;
        std::vector<double> _pendVec;
};

#endif