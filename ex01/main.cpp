#include "RPN.hpp"

int main(int argc, char **argv)
{
    if (argc != 2) {
        std::cout << "ERROR" << std::endl;
    } else {
        RPN rpn(argv[1]);
        rpn.calc();
    }
    return 0;
}