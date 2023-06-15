#include "RPN.hpp"

int main(int argc, char **argv)
{
    RPN rpn(argv[1]);
    rpn.calc();
    return 0;
}