#include "RPN.hpp"

bool isNumber(std::string numStr)
{
    bool dot = false;
    for (size_t i = 0; i < numStr.size(); ++i) {
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

bool RPN::isOperator(std::string op)
{
    std::string opers = "+-*/";
    if (op.size() > 1)
        return false;
    if (opers.find(op[0]) == std::string::npos)
        return false;
    return true;

}

//public
void RPN::calc()
{
    double num1;
    double num2;
    double result;

    for (inputIter it = this->_input.begin(); it != this->_input.end(); ++it) {
        if (!isNumber(*it) && !this->isOperator((*it))) {
            std::cout << "ERROR" << std::endl;
            exit(0);
        }
		if (this->_input.size() == 1) {
			std::cout << "result: " << *it << std::endl;
			exit(0);
		}
        if (this->isOperator(*it)) {
            if (this->_stack.size() < 2) {
                std::cout << "ERROR" << std::endl;
                exit(0);
            }
            num2 = this->_stack.front();
            this->_stack.pop_front();
            num1 = this->_stack.front();
            this->_stack.pop_front();
            if (*it == "+")
                result = num1 + num2;
            if (*it == "-")
                result = num1 - num2;
            if (*it == "*")
                result = num1 * num2;
            if (*it == "/")
                result = num1 / num2;
            this->_stack.push_front(result);
        } else {
            double num = atof((*it).c_str());
            this->_stack.push_front(num);
        }
    }
    if (this->_stack.size() != 1) {
        std::cout << "ERROR" << std::endl;
        exit(0);
    } else {
        this->_stack.pop_front();
        std::cout << "result: " << result << std::endl;
    }
}
//canonical

RPN::RPN(const RPN& src)
{
    *this = src;
}

RPN& RPN::operator=(const RPN& rhs) 
{
    if (this != &rhs) {
        *this = rhs;
    }
    return *this;
}