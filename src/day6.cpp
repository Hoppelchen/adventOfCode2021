#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

constexpr int NUM_STEP = 80;

class Lanternfish
{
    private:
        short timer = 0;

    public:
        Lanternfish()
        {
            timer = 8;
        }

        Lanternfish(short start)
        {
            timer = start;
        }

        bool proceed()
        {
            if (timer == 0)
            {
                timer = 6;
                return true;
            }

            timer--;

            return false;
        }

        int getTimer()
        {
            return timer;
        }

};

void printState(std::vector<Lanternfish> &fish, int step)
{
    if (step == 0)
    {
        std::cout << "Initial state: ";
    }
    else
    {
        std::cout << "After " << step << " days: ";
    }

    /*
    for(auto& f : fish)
    {
        std::cout << f.getTimer() << ",";
    }
    */

    std::cout << std::endl;
    
}

void proceed(std::vector<Lanternfish> &fish)
{
    int newFish = 0;
    for(auto& f : fish)
    {
        if (f.proceed())
        {
            newFish++;
        }
    }

    for (int i = 0; i < newFish; i++)
    {
        fish.push_back(Lanternfish());
    }
}

int main()
{
    std::ifstream infile("input/day6_example");
    std::string line;
    std::vector<Lanternfish> fish;

    while (infile >> line)
    {

        std::stringstream  stringstream(line);
        for (int i; stringstream >> i;)
        {
            fish.push_back(Lanternfish(i));    
            if (stringstream.peek() == ',')
            {
                stringstream.ignore();
            }
        }

        break;
    }

    for (int i = 1; i <= NUM_STEP; i++)
    {
        proceed(fish);
        printState(fish, i);
    }

    std::cout << "result: "  << fish.size() << std::endl;

    return 0;
}