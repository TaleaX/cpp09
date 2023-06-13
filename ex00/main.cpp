# include "BitcoinExchange.hpp"

int main (int argc, char **argv)
{
    if (argc < 2)
        std::cerr << "Error: could not open file" << std::endl;
    else {
        BitcoinExchange bitExchange;
        bitExchange.readInputFile(argv[1]);
    }
    return 0;
}