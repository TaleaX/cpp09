#include "PMergeMe.hpp"

int main(int argc, char **argv)
{
    if (argc < 2) {
        std::cout << "Error" << std::endl;
    } else {
        PMergeMe mergeLst((argv + 1));
        mergeLst.sort();
    }
    return 0;
}