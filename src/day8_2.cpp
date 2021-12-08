#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <assert.h>
#include <regex>

constexpr int RESULT_LEN = 4;
const std::string SEPERATOR = "|";
enum PARSER {PARSER_INPUT, PARSER_RESULT};

bool contains(std::string input, std::string checks)
{
    for(char& c : checks) 
    {
        if (input.find(c) == std::string::npos)
        {
            return false;
        }
    }

    return true;
}

bool containsAll(std::string input, std::string checks)
{
    if (input.size() != checks.size())
    {
        return false;
    }

    return contains(input, checks);
}

void printLookup(std::map<int, std::string> &lookup)
{
    for (const auto& [key, value] : lookup) {
        std::cout << key << " has value " << value << std::endl;
    }
}

int main()
{
    int cnt;
    std::ifstream infile("input/day8");
    std::string string;
    std::vector<std::string> input;
    std::vector<std::string> result;
    
    std::map<int, std::string> lookup;

    PARSER parserState = PARSER_INPUT;

    int overallResult = 0;
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
                    input.push_back(string);

                    break;
                
                case PARSER_RESULT:
                    result.push_back(string);
                    cnt++;

                    if (cnt == 4)
                    {
                        parserState = PARSER_INPUT;

                        // parse result, first get the simple ones
                        for(auto& str : input)
                        {
                            switch (str.size())
                            {
                                case 2:
                                    lookup[1] = str;
                                    break;
                                case 3:
                                    lookup[7] = str;
                                    break;
                                case 4:
                                    lookup[4] = str;
                                    break;
                                case 7:
                                    lookup[8] = str;
                                    break;
                                
                                default:
                                    break;
                            }
                        }

                        // assumption, 1 and 4 is always in the string :)
                        assert(lookup[1].compare("") != 0);
                        assert(lookup[4].compare("") != 0);
                        
                        for(auto& str : input)
                        {
                            if(str.size() == 6)
                            {
                                if (contains(str, lookup[1]) == false)
                                {
                                    lookup[6] = str;
                                }
                                else if (contains(str, lookup[4]))
                                {
                                    lookup[9] = str;
                                }
                                else
                                {
                                    lookup[0] = str;
                                }
                            }
                            else if (str.size() == 5)
                            {
                                if (contains(str, lookup[1]))
                                {
                                    lookup[3] = str;
                                }
                                else
                                {
                                    std::string copy = lookup[4];
                                    for(char &c : str)
                                    {
                                        std::string dummy(1, c);
                                        copy = std::regex_replace(copy, std::regex(dummy), "");
                                    }

                                    if (copy.size() == 2)
                                    {
                                        lookup[2] = str;
                                    }
                                    else
                                    {
                                        lookup[5] = str;
                                    }
                                }
                            }
                        }


                        // then check result
                        //printLookup(lookup);

                        int mult = 1000;
                        int value = 0;
                        for (auto &res : result)
                        {
                            std::cout << res << " ";
                            for (int i = 0; i < 10; i++)
                            {
                                if (containsAll(lookup[i], res))
                                {   
                                    value += i*mult;

                                    break;
                                }
                            }

                            mult = mult / 10;
                        }
                        std::cout << std::endl;
                        std::cout << "res: " <<  value << std::endl;
                        overallResult +=value;
                        lookup = {};
                        input.clear();
                        result.clear();
                    }

                    break;
            }
        }
    }


    std::cout << "Final Result: " << overallResult << std::endl;

    return 0;
}