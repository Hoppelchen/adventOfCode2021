#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

const int BOARD_X = 5;
const int BOARD_Y = 5;

enum STATE { STATE_DRAWN_NUMBERS, STATE_NEW_BOARD, STATE_GREP_BOARD_INPUT };

class Board
{
    private:
        int data[BOARD_X][BOARD_Y] = {};
        bool hit[BOARD_X][BOARD_Y] = {};
        int filled = 0;

        int rowResult(int row)
        {
            int result = 0;
            for (int i = 0; i < BOARD_X; i++)
            {
                result += data[i][row];
                
            }

            return result;
        }

        int columnResult(int column)
        {
            int result = 0;
            for (int i = 0; i < BOARD_Y; i++)
            {
                result += data[column][i];
                
            }

            return result;
        }

        bool rowFinished(int row)
        {
            for (int i = 0; i < BOARD_X; i++)
            {
                if (hit[i][row] == false)
                {
                    return false;
                }
            }

            return true;
        }

        bool columnFinished(int column)
        {
            for (int i = 0; i < BOARD_Y; i++)
            {
                if (hit[column][i] == false)
                {
                    return false;
                }
            }

            return true;
        }
    public:
        Board()
        {
            std::cout << "constr" << std::endl;
        }

        bool addData(int value)
        {
            data[filled % BOARD_X][filled / BOARD_Y] = value;
            filled++;
            return filled == BOARD_X * BOARD_Y;
        }

        void addNumber(int value)
        {
            for(int i = 0; i < BOARD_Y; i++)
            {
                 for(int j = 0; j < BOARD_X; j++)
                 {
                    if(data[j][i] == value)
                    {
                        hit[j][i] = true;
                    }
                 }
            }
        }

        int finished()
        {
            // check lines
            for (int i = 0; i < BOARD_Y; i++)
            {
                if(rowFinished(i))
                {
                    return rowResult(i);
                }
            }

            for (int i = 0; i < BOARD_X; i++)
            {
                if(columnFinished(i))
                {
                    return columnResult(i);
                }
            }

            return 0;
        } 

        int sumUnmarked()
        {
            int result = 0;

            for(int i = 0; i < BOARD_Y; i++)
            {
                 for(int j = 0; j < BOARD_X; j++)
                 {
                    if(hit[j][i] == false)
                    {
                        result += data[j][i];
                    }
                 }
            }

            return result;
        }

        void print()
        {
            std::cout << "Board:" << std::endl;
            for(int i = 0; i < BOARD_Y; i++)
            {
                 for(int j = 0; j < BOARD_X; j++)
                 {
                    if (hit[j][i])
                    {
                        std::cout << "(" <<data[j][i] << ") ";
                    }
                    else
                    {
                        std::cout << data[j][i] << " ";
                    }
                    
                 }
                 std::cout << std::endl;
            }
        }

};


int main()
{
   
    std::ifstream infile("input/day4");
    std::string line;
    STATE state = STATE_DRAWN_NUMBERS;
    std::vector<int> drawnNumbers;
    std::vector<Board> boards;

    while (infile >> line)
    {
        switch(state)
        {
            case STATE_DRAWN_NUMBERS:
            {
                // parse number input
                std::stringstream  stringstream(line);

                for (int i; stringstream >> i;)
                {
                    drawnNumbers.push_back(i);    
                    if (stringstream.peek() == ',')
                    {
                        stringstream.ignore();
                    }
                }

                state = STATE_NEW_BOARD;

                break;
            }

            case STATE_NEW_BOARD:
            {
                std::cout << "new board" << std::endl;
                Board board;

                boards.push_back(board);

                state = STATE_GREP_BOARD_INPUT;
            }

            case STATE_GREP_BOARD_INPUT:
            {
                std::cout << "board input " << line << std::endl;
                Board &board = boards.back();

                if(board.addData(std::stoi(line)))
                {
                    std::cout << "board filled" << std::endl;
                    state = STATE_NEW_BOARD;
                }

                break;
            }

        }

        
    }

    std::cout << "drawnNumbers";
    for(const auto &number: drawnNumbers)
    {
        std::cout << number << std::endl;

        for(Board &board : boards)
        {
            if (board.finished() == 0)
            {
                board.addNumber(number);
                if (board.finished() != 0)
                {
                    std::cout << "Finished: " << number << "*" << board.sumUnmarked() << "=" << number * board.sumUnmarked() << std::endl;
                    board.print();
                }
            }
        }
    }

    std::cout << std::endl;

   

    return 0;
}