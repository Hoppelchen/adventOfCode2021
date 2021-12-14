#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <utility>
#include <assert.h>
#include <algorithm>

class Polymer
{
    private:
        std::vector<char> currentPolymer;
        std::map<std::pair<char, char>,char> rules;

    public:
        Polymer(std::string startPolymer)
        {
            currentPolymer = std::vector(startPolymer.begin(), startPolymer.end());
        }

        void addRule(std::string rule, std::string insert)
        {
            assert(rule.size() == 2);
            assert(insert.size() == 1);

            rules[std::pair(rule[0], rule[1])] = insert[0];
        }

        void performRound()
        {
            std::vector<char> result;
            for (size_t i = 1; i < currentPolymer.size(); i++)
            {
                std::pair<char, char> key(currentPolymer[i-1], currentPolymer[i]);
                result.push_back(currentPolymer[i-1]);
                result.push_back(rules[key]);
            }

            result.push_back(currentPolymer.back());

            currentPolymer = result;
        }

        int getResult()
        {
            std::map<char, int> resultMap;

            for(auto &ch : currentPolymer)
            {
                resultMap[ch]++;
            }

            std::vector<int> result;
            for (const auto& [key, value] : resultMap)
            {
                result.push_back(value);
            }

            std::sort(result.begin(), result.end());

            return result.back() - result.front();
        }

        std::string getPolymer()
        {
            return std::string(currentPolymer.begin(), currentPolymer.end());
        }
};

int main()
{
    std::ifstream infile("input/day14");
    std::string input;
    std::string previous;

    std::getline(infile, input);

    Polymer polymer(input);


    while (infile >> input)
    {
        if (input.compare("->") == 0)
        {
            continue;
        }

        if (input.size() == 1)
        {
            polymer.addRule(previous, input);
        }
        else
        {
             previous = input;
        }
       
        
        
    }

    for (int i = 0; i < 10; i++)
    {
        polymer.performRound();
        std::cout << (i+1) << std::endl;
    }

    std::cout << "result = " << polymer.getResult() << std::endl;

    return 0;
}