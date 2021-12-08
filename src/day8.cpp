#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>

constexpr int RESULT_LEN = 4;
const std::string SEPERATOR = "|";
enum PARSER {PARSER_INPUT, PARSER_RESULT};


int getValue(std::string input)
{
    switch(input.size())
    {
        case 2:
            return 1;
        case 3:
            return 7;
        case 4:
            return 4;
        case 7: 
            return 8;
        default:
            return -1;
    }
}


int main()
{
    int cnt;
    std::ifstream infile("input/day8");
    std::string string;
    
    PARSER parserState = PARSER_INPUT;

    int result = 0;

    while (infile >> string)
    {
        if (string.compare(SEPERATOR) == 0)
        {
            parserState = PARSER_RESULT;
            cnt = 0;
        }
        else
        {
            switch (parserState)
            {
                case PARSER_INPUT:
                    

                    std::cout << "input: " << string << std::endl;

                    

                    break;
                
                case PARSER_RESULT:
                    std::cout << "result: " << string << std::endl;
                    cnt++;

                    if (getValue(string) != -1)
                    {
                        result++;
                        std::cout << "Result: " << result << std::endl;
                    }

                    if (cnt == RESULT_LEN)
                    {
                        parserState = PARSER_INPUT;
                    }

                    break;
            }
        }
    }

    std::cout << "Result: " << result << std::endl;

    return 0;
}