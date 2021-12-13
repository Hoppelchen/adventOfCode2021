#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>

enum STATE {STATE_COORDS, STATE_FOLD};

class Board
{
    private:
        std::vector<std::pair<int,int>> inputData;
        std::vector<std::vector<char>> board;

        void print(std::vector<std::vector<char>> &data)
        {
            std::cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << std::endl;
            for (size_t y = 0; y < data.size(); y++)
            {
                for (size_t x = 0; x < data[y].size(); x++)
                {
                    std::cout << data[y][x];
                }

                std::cout << std::endl;
            }
        }

    public:
        Board()
        {}

        void addData(std::string line)
        {
            std::stringstream  stringstream(line);

            std::vector<int> input;

            for (int i; stringstream >> i;)
            {
                input.push_back(i);    
                if (stringstream.peek() == ',')
                {
                    stringstream.ignore();
                }
            }

            std::pair<int, int> data(input[1], input[0]);
            inputData.push_back(data);
        }

        void buildBoard()
        {
            std::pair<int,int> biggest(0,0);

            // get biggest to get board dimensions
            for(auto &input : inputData)
            {
                if (input.first > biggest.first)
                {
                    biggest.first = input.first;
                }

                if (input.second > biggest.second)
                {
                    biggest.second = input.second;
                }
            }

            board = std::vector<std::vector<char>>(biggest.first + 1, std::vector<char>(biggest.second + 1, '.'));

            // addDots
            for(auto &input : inputData)
            {
                board[input.first][input.second] = '#';
            }

        }

        void print()
        {
            print(board);
        }

        int getDots()
        {
            int dots = 0;
            for (size_t y = 0; y < board.size(); y++)
            {
                for (size_t x = 0; x < board[y].size(); x++)
                {
                    if(board[y][x] == '#')
                    {
                        dots++;
                    }
                }
            }

            return dots;
        }

        void foldY(int at)
        {
            for (size_t y = 0; y < board.size() - at; y++)
            {
                for (size_t x = 0; x < board[y].size(); x++)
                {
                    if (board[at - y][x] == '#' || board[at + y][x] == '#')
                    {
                        board[at - y][x] = '#';
                    }
                }
            }

            board = std::vector<std::vector<char>>(board.begin(), board.begin() + at);       
        }

        void foldX(int at)
        {
           for (size_t y = 0; y < board.size(); y++)
            {
                for (size_t x = 0; x < board[y].size() - at; x++)
                {
                    if (board[y][at - x] == '#' || board[y][at + x] == '#')
                    {
                        board[y][at - x] = '#';
                    }
                }
            }


            for (size_t y = 0; y < board.size(); y++)
            {
                board[y] = std::vector<char>(board[y].begin(), board[y].begin() + at);
            }
        }
};

int main()
{  
    STATE state = STATE_COORDS;
    std::string line;
    std::ifstream infile("input/day13");
    Board board;
   
    while (infile >> line)
    {
        if (line[0] == 'f' && state != STATE_FOLD)
        {
            state = STATE_FOLD;
            board.buildBoard();
        }

        switch (state)
        {
        case STATE_COORDS:
            board.addData(line);
            break;

        case STATE_FOLD:
        {
            std::stringstream  stringstream(line);

            if(line[0] == 'x')
            {
                stringstream.seekg(2);
                for (int i; stringstream >> i;)
                {
                    board.foldX(i);
                    std::cout << "dots: " << board.getDots() << std::endl;
                }
            }
            else if (line[0] == 'y')
            {
                stringstream.seekg(2);
                for (int i; stringstream >> i;)
                {
                    board.foldY(i);
                    std::cout << "dots: " << board.getDots() << std::endl;
                    
                }
            }

            break;
        }
        
        default:
            break;
        }
    }

    board.print();

    return 0;
}