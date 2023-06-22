#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
    if (argc < 2) {
        std::cout << "Error" << std::endl;
    } else {
        PmergeMe mergeLst((argv + 1));
        clock_t begin = clock();
        mergeLst.sort();
        clock_t end = clock();
        double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    }
    return 0;
}