#ifndef __PMERGEME__
# define __PMERGEME__

# include <list>
# include <vector>
# include <array>
# include <iostream>
# include <sstream>

typedef std::list<std::array<double, 2>>::iterator pairsIter;
typedef std::vector<std::string>::iterator inpIter;
typedef std::string::iterator strIter;

class PMergeMe
{
    public:
        PMergeMe& operator=(const PMergeMe& rhs);
        PMergeMe(const PMergeMe& src);
        PMergeMe(char **argv);
        PMergeMe(){}
        ~PMergeMe(){}
    private:
        int _size;
        std::list<std::array<double, 2>> _pairs;
        std::vector<std::string> _input;
        double  _straddler;
};

#endif