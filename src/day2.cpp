#include <iostream>
#include <string>
#include <fstream>


int main()
{
    std::ifstream infile("input/day2");
    std::string direction;
    int amount = 0;

    int horizontal = 0;
    int depth = 0;



    while (infile >> direction >> amount)
    {
        std::cout << direction << "::" << amount << std::endl;

        if (direction.compare("forward") == 0)
        {
            horizontal += amount;
        }
        else if (direction.compare("down") == 0)
        {
            depth += amount;
        }
        else if (direction.compare("up") == 0)
        {
            depth -= amount;
        }
    }

    std::cout << "horizontal=" << horizontal << std::endl;
    std::cout << "depth=" << depth << std::endl;
    std::cout << "result=" << (horizontal * depth) << std::endl;

    return 0;
}