#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

class Board
{
    private:
        std::vector<std::string> input;
        int xSize;
        int ySize;
        std::vector<std::vector<int>> data;

    private:
        int getBasinRec(int x, int y)
        {
            if (data[y][x] == 9)
            {
                return 0;
            }
            else
            {
                // mark as visited
                data[y][x] = 9;
                if (y == 0)
                {
                    if (x == 0)
                    {
                        // unten + rechts
                        return 1 + getBasinRec(x, y+1) + getBasinRec(x+1, y);
                        
                    }
                    else if (x == xSize - 1)
                    {
                        // unten + links
                        return 1 + getBasinRec(x, y + 1) + getBasinRec(x-1, y);
                    }
                    else
                    {
                        // unten + links + rechts
                        return 1 + getBasinRec(x, y+1) + getBasinRec(x-1, y) + getBasinRec(x+1, y);
                    }
                }
                else if (y == ySize - 1)
                {
                    if (x == 0)
                    {
                        // oben + rechts
                        return 1 + getBasinRec(x, y-1) + getBasinRec(x+1, y);
                    }
                    else if (x == xSize - 1)
                    {
                        // oben + links
                        return 1 + getBasinRec(x, y-1) + getBasinRec(x-1, y);
                    }
                    else
                    {
                        // oben + links + rechts
                        return 1 + getBasinRec(x, y-1) + getBasinRec(x-1, y) + getBasinRec(x+1, y);
                    }
                }
                else
                {
                    if (x == 0)
                    {
                        // unten + rechts + oben
                        return 1 + getBasinRec(x, y+1) + getBasinRec(x+1, y) + getBasinRec(x, y-1);
                    }
                    else if (x == xSize - 1)
                    {
                        // unten + links + oben
                        return 1 + getBasinRec(x, y+1) + getBasinRec(x-1, y) + getBasinRec(x, y-1);
                    }
                    else
                    {
                        // alle 4 richtungen
                        return 1 + getBasinRec(x, y+1) + getBasinRec(x-1, y) + getBasinRec(x, y-1) + getBasinRec(x+1, y);
                    }
                }
            }
        }

        bool isMinima(int x, int y)
        {
            int element = data[y][x];
            // check edges
            if (y == 0)
            {
                if (x == 0)
                {
                    // unten + rechts
                    if (element < data[y+1][x] && element < data[y][x+1])
                    {
                        return true;
                    }
                }
                else if (x == xSize - 1)
                {
                     // unten + links
                    if (element < data[y+1][x] && element < data[y][x-1])
                    {
                        return true;
                    }
                }
                else
                {
                    // unten + links + rechts
                    if (element < data[y+1][x] && element < data[y][x-1] && element < data[y][x+1])
                    {
                        return true;
                    }
                }
            }
            else if (y == ySize - 1)
            {
                if (x == 0)
                {
                    // oben + rechts
                    if (element < data[y-1][x] && element < data[y][x+1])
                    {
                        return true;
                    }
                }
                else if (x == xSize - 1)
                {
                     // oben + links
                    if (element < data[y-1][x] && element < data[y][x-1])
                    {
                        return true;
                    }
                }
                else
                {
                     // oben + links + rechts
                    if (element < data[y-1][x] && element < data[y][x-1] && element < data[y][x+1])
                    {
                        return true;
                    }
                }
            }
            else
            {
                if (x == 0)
                {
                    // unten + rechts + oben
                    if (element < data[y+1][x] && element < data[y][x+1] && element < data[y-1][x])
                    {
                        return true;
                    }
                }
                else if (x == xSize - 1)
                {
                     // unten + links + oben
                    if (element < data[y+1][x] && element < data[y][x-1] && element < data[y-1][x])
                    {
                        return true;
                    }
                }
                else
                {
                    // alle 4 richtungen
                    if (element < data[y+1][x] && element < data[y][x-1] && element < data[y-1][x]  && element < data[y][x+1])
                    {
                        return true;
                    }
                }
            }

            return false;
        }

    public:
        Board()
        {}

        void addLine(std::string line)
        {
            input.push_back(line);
        }

        void parseData()
        {
            ySize = input.size();
            xSize = input[0].size();

            data = std::vector<std::vector<int>>(ySize, std::vector<int>(xSize, 0));


            for (size_t y = 0; y < input.size(); y++)
            {
                std::string &line = input[y];
                for (size_t x = 0; x < line.size(); x++)
                {
                    char &ch = line[x];
                    data[y][x] = ch - '0';
                }
            }
        }

        std::vector<int> getMinima()
        {
            std::vector<int> result;

            for(size_t y = 0; y < data.size(); y++)
            {
                std::vector<int> row = data[y];
                for(size_t x = 0; x < row.size(); x++)
                {
                    if (isMinima(x, y))
                    {
                        std::cout << "found! x:" << x << " y:" << y << " val" << data[y][x] << std::endl; 
                        result.push_back(getBasinRec(x, y));
                    }
                }
            }

            return result;
        }


};

int main()
{
    std::ifstream infile("input/day9");
    std::string input;
    int res;

    Board board;

    while (infile >> input)
    {
        std::cout << input << std::endl;
        board.addLine(input);
    }

    board.parseData();

    std::vector<int> result = board.getMinima();
    std::sort(result.begin(), result.end(), std::greater<int>());

    res = result[0];
    for (int i = 1; i < 3; ++i)
    {
        res *= result[i];
       
    }

    std::cout << "Result: " << res << std::endl;

    return 0;
}