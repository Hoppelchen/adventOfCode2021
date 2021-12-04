#include <iostream>
#include <string>
#include <fstream>
#include <vector>

int main()
{
    std::ifstream infile("input/day1");
    std::vector<int> data = {};
    int count = 0;
    int a = 0;
    while (infile >> a)
    {
        data.push_back(a);
    }

    std::cout << data[0] + data[1] + data[2] << " (N/A - no previous measurement)" << std::endl;
    for (int i = 3; i < (int)data.size(); i++)
    {
        std::cout << data[i] + data[i - 1] + data[i - 2];
        if (data[i - 1] + data[i - 2] + data[i - 3] < data[i] + data[i - 1] + data[i - 2])
        {
            std::cout << " (increased)" << std::endl;
            count++;
        }
        else if (data[i - 1] + data[i - 2] + data[i - 3] > data[i] + data[i - 1] + data[i - 2])
        {
            std::cout << " (decreased)" << std::endl;
        }
        else
        {
            std::cout << " (no change)" << std::endl;
        }
    }

    std::cout << "Result: " << count << std::endl;

    return 0;
}