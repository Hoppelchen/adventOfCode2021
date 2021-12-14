#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <utility>
#include <assert.h>
#include <algorithm>
#include <math.h>

class Polymer
{
    private:
        std::map<std::string, int64_t> polymerCount;
        std::map<std::string, std::string> rules;
        std::string polymer;


    public:
        Polymer(std::string startPolymer)
        {
            // initial anzahl setzen, wie bei laternen fische über anzahl gehen, nicht jedes einzeln betrachten
            for (size_t i = 1; i < startPolymer.size(); i++)
            {
                polymerCount[startPolymer.substr((i-1), 2)] = 1;
            }
            
            polymer = startPolymer;
        }

        void addRule(std::string rule, std::string result)
        {
            rules[rule] = result;
        }

        void performRound()
        {
            std::map<std::string, int64_t> newCount;
            for (const auto& [rule, insert] : rules)
            {
                // wenn wir eine regel noch nicht gesehen haben können wir diese überspringen
                if (polymerCount.find(rule) == polymerCount.end())
                {
                    continue;
                }

                // update appearances
                int64_t count = polymerCount[rule];
                std::string left = rule[0] + insert;
                std::string right = insert + rule[1];

                newCount[left] += count;
                newCount[right] += count;
            }

            polymerCount = newCount;
        }

        int64_t getResult()
        {
            std::map<char, int64_t> appearance;
            std::vector<int64_t> result;

            for (const auto& [rule, count] : polymerCount)
            {
                for (auto &ch : rule)
                {
                    appearance[ch] += count;
                }
            }

            // da vorne und hinten buchstaben nur einzeln stehen aber alle anderen doppelt gezäht sind erstmal erhöhen und nacher dann alles durch 2
            appearance[polymer.front()]++;
            appearance[polymer.back()]++;

            for (const auto& [ch, count] : appearance)
            {
                result.push_back(appearance[ch] / 2);
            }

            std::sort(result.begin(), result.end());

            return result.back() - result.front();
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


    for (int i = 0; i < 40; i++)
    {
        polymer.performRound();
    }

    std::cout << "result = " << polymer.getResult() << std::endl;
    
    return 0;
}