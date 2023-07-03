#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
    if (argc < 2) {
        std::cout << "Error" << std::endl;
    } else {
        PmergeMe mergeLst;
        mergeLst.sort((argv + 1));
    }
    return 0;
}