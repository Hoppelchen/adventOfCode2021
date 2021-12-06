#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

constexpr int NUM_STEP = 256;

int main()
{
    std::ifstream infile("input/day6");
    std::string line;
    std::vector<int64_t> states(9, 0);

    while (infile >> line)
    {

        std::stringstream  stringstream(line);
        for (short i; stringstream >> i;)
        {
            states[i]++;
            if (stringstream.peek() == ',')
            {
                stringstream.ignore();
            }
        }

        break;
    }

    for (int i = 1; i <= NUM_STEP; i++)
    {   
        // store fish with 0 lifetime as new fish and also to reset as 6 days;
        int64_t newFish = states[0];
        for(size_t statePos = 0; statePos < states.size() - 1; statePos++)
        {
           states[statePos] = states[statePos + 1];
        }

        // reset fish to pos 6
        states[6] += newFish;

        // add new fish
        states[8] = newFish;

        std::cout << "After " << i << " days: " << std::endl;
    }

    int64_t result = 0;

    for (auto fish : states)
    {
        result += fish;
    }

    std::cout << "result: "  << result << std::endl;

    return 0;
}