#ifndef __PMERGEME__
# define __PMERGEME__

# include <list>
# include <vector>
# include <array>
# include <iostream>
# include <sstream>
# include <cmath>

typedef std::list<std::array<double, 2>>::iterator pairsIter;
typedef std::vector<std::string>::iterator inpIter;
typedef std::string::iterator strIter;

class PMergeMe
{
    public:
        void sort();
        PMergeMe& operator=(const PMergeMe& rhs);
        PMergeMe(const PMergeMe& src);
        PMergeMe(char **argv);
        PMergeMe(){}
        ~PMergeMe(){}
    private:
        void splitIntoPairs();
        void sortPairs();
        void insertionSortPairs();
        void finalSort();
        int getNextJacobsthalNum(int iterCount, int currentNum);
        void insertPendNum(int tagNum);
        double getElementByIndex(int index);
        std::list<double>::iterator getIteratorByIndex(int index);
        int _size;
        std::list<std::array<double, 2>> _pairs;
        std::list<double> _output;
        std::vector<double> _pend;
        std::vector<std::string> _input;
        double  _straddler;
};

#endif