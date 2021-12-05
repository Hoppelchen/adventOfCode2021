#include <iostream>
#include <string>
#include <fstream>
#include <utility>
#include <sstream>
#include <vector>
#include <memory>
#include <regex>


constexpr int MAX_SIZE_X = 1000;
constexpr int MAX_SIZE_Y = 1000;

enum DIRECTION { DIRECTION_X, DIRECTION_Y, DIRECTION_OTHER };

class Command
{
    private:
        std::pair<int,int> start;
        std::pair<int,int> end;
    public:
        Command(std::string command)
        {
            std::vector<int> input;
            int a;

            command = std::regex_replace(command, std::regex(","), " ");
            command = std::regex_replace(command, std::regex(" -> "), " ");

            std::stringstream  stringstream(command);
            while (stringstream >> a)
            {
                input.push_back(a);
            }

            start = std::pair<int, int>(input[0], input[1]);
            end = std::pair<int, int>(input[2], input[3]);
        }

        void print()
        {
            std::cout << "Start X:" << start.first << " Y:" << start.second <<std::endl;
            std::cout << "End   X:" << end.first << " Y:" << end.second <<std::endl;
        }

        // x == 0 => 0, y == 0 => 1, else 2 
        DIRECTION getDirection()
        {
            if (start.first == end.first)
            {
                return DIRECTION_Y;
            }
            else if (start.second == end.second)
            {
                return DIRECTION_X;
            }

            return DIRECTION_OTHER;
        }

        int getDistance()
        {
            if(getDirection() == DIRECTION_Y)
            {
                return end.second - start.second;
            }
            else if(getDirection() == DIRECTION_X)
            {
               return end.first - start.first;
            }
            else
            {
                return 0;
            }
        }

        int getStartX()
        {
            return start.first;
        }

        int getStartY()
        {
            return start.second;
        }

};

class Board
{
    private:
       std::array<std::array<int, MAX_SIZE_X>, MAX_SIZE_Y> field  = {};

    public:
        void print()
        {
            for(auto& rows: field)
            {
                for(auto& elem: rows)
                {
                    if (elem == 0)
                    {
                        std::cout << ".";
                    }
                    else
                    {
                        std::cout << elem;
                    }
                    
                }

                std::cout << std::endl;
            }
        }

        void addCommand(Command &cmd)
        {
            int x = cmd.getStartX();
            int y = cmd.getStartY();

            if (cmd.getDistance() > 0)
            {
                switch (cmd.getDirection())
                {
                    case DIRECTION_X:
                        for (int i = x; i <= x + cmd.getDistance(); i++)
                        {
                            field[y][i]++;
                        }
                        break;
                
                    case DIRECTION_Y:
                        for (int i = y; i <= y + cmd.getDistance(); i++)
                        {
                            field[i][x]++;
                        }
                        break;

                    case DIRECTION_OTHER:
                        std::cout << "ignore" << std::endl;
                        break;
                }
            }
            else if (cmd.getDistance() < 0)
            {
                switch (cmd.getDirection())
                {
                    case DIRECTION_X:
                        for (int i = x + cmd.getDistance(); i <= x; i++)
                        {
                            field[y][i]++;
                        }
                        break;
                
                    case DIRECTION_Y:
                        for (int i = y + cmd.getDistance(); i <= y; i++)
                        {
                            field[i][x]++;
                        }
                        break;

                    case DIRECTION_OTHER:
                        std::cout << "ignore" << std::endl;
                        break;
                }
            }

            
        }

        int result()
        {
            int result = 0;

            for(auto& rows: field)
            {
                for(auto& elem: rows)
                {
                    if (elem >= 2)
                    {
                       result++;
                    }
                }
            }

            return result;
        }
};


int main()
{
    std::ifstream infile("input/day5");
    std::string line;
    std::vector<Command> commands;
    std::shared_ptr<Board> field = std::make_shared<Board>();

    while (std::getline(infile, line))
    {
        std::cout << line << std::endl;

        commands.push_back(Command(line));
    }
    for (auto &cmd : commands)
    {
        field->addCommand(cmd);
        cmd.print();
    }

    //field.print();
    std::cout << "Result = " << field->result() << std::endl;

    return 0;
}