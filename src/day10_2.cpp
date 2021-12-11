#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>

class Stack
{
    private:
        std::map<char, int> lookup = {{')', 1}, {']', 2}, {'}', 3}, {'>', 4}};
        std::string data;
        bool isOpeningBrace(char ch)
        {
            return (ch == '(') || (ch == '[') || (ch == '{') || (ch == '<');
        }

        bool isClosing(char opening, char closing)
        {
            // über ascii tabelle
            return abs (opening - closing) <= 2;
        }

        char getClosingBrace(char ch)
        {
            if (ch == '(')
            {
                return ch + 1;
            }

            return ch + 2;
        }

    public:
        Stack(std::string input)
        {
            data = input;
        }

    int64_t check()
    {
        std::vector<char> stack;
        int64_t res = 0;

        for (size_t i = 0; i < data.size(); i++)
        {
            if (isOpeningBrace(data[i]))
            {
                stack.push_back(data[i]);
            }
            else
            {
                char opening = stack.back();
                stack.pop_back();

                if (!isClosing(opening, data[i]))
                {
                    return 0;
                }
            }
        }

        if (stack.size() > 0)
        {
            while(stack.size() > 0)
            {
                char opening = stack.back();
                stack.pop_back();

                res *= 5;
                res += lookup[(getClosingBrace(opening))];
            }
            
            return res;
        }

        return 0;
    }
};


int main()
{
    std::ifstream infile("input/day10");
    std::string input;
    std::vector<int64_t> res;

    while (infile >> input)
    {
        Stack stack(input);
        int64_t result = stack.check();
        if (result != 0)
        {
            res.push_back(result);
        }
    }

    std::sort(res.begin(), res.end(), std::greater<int64_t>());

    // always odd
    int index = res.size() / 2;

    std::cout << "res = " << res[index] << std::endl;

    return 0;
}