#include <iostream>
#include <fstream>
#include "CSVParser.h"

int main()
{

    std::ifstream fileName("input1.csv");

    try
    {
        CSVParser<int, std::string, std::string, int, double, std::string> csvParser(fileName);
        for (const std::tuple<int, std::string, std::string, int, double, std::string> rs : csvParser)
        {
            std::cout << rs << std::endl;
        }
    }
    catch (my_exception &ex)
    {
        std::cout << ex.what() << std::endl;
        return 1;
    }

    return 0;
}