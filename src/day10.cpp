#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>



class Stack
{
    private:
        std::map<char, int> lookup = {{')', 3}, {']', 57}, {'}', 1197}, {'>', 25137}};
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

    public:
        Stack(std::string input)
        {
            data = input;
        }

    int check()
    {
        std::vector<char> stack;

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
                    return lookup[data[i]];
                }
            }
        }

        return 0;
    }
};





int main()
{
    std::ifstream infile("input/day10");
    std::string input;
    int res = 0;

    while (infile >> input)
    {
        Stack stack(input);

        res += stack.check();
    }

    std::cout << "res = " << res << std::endl;

    return 0;
}