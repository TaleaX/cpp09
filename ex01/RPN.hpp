#ifndef __RPN__
# define __RPN__

# include <deque>
# include <iostream>
# include <sstream>
# include <cstdlib>

typedef std::deque<double>::iterator stackIter;
typedef std::deque<std::string>::iterator inputIter;
typedef std::string::iterator strIter;

class RPN
{
    public:
        void calc();
        RPN& operator=(const RPN& rhs);
        RPN(const RPN& src);
        RPN(std::string input) {
            std::stringstream iss(input);
            std::string token;
            while (getline(iss, token, ' ')) {
                this->_input.push_back(token);
           }
        }
        RPN(){}
        ~RPN(){}
    private:
        bool isOperator(std::string op);
        std::deque<double> _stack;
        std::deque<std::string> _input;
};

#endif