#include <iostream>
#include <string>
#include <fstream>
#include <vector>

class Board
{
    private:
        std::vector<std::vector<int>> map;
        std::vector<std::vector<bool>> flashedMap;
        std::vector<std::string> inputData;

        int xSize;
        int ySize;

        int doFlash(int y, int x)
        {
            // diagonalen
            if ((y + 1) < ySize && (x + 1) < xSize)
            {
                map[y+1][x+1]++;
            }
            if ((y + 1) < ySize && (x - 1) >= 0)
            {
                map[y+1][x-1]++;
            }

            if ((y - 1) >= 0 && (x + 1) < xSize)
            {
               map[y-1][x+1]++;
            }
            if ((y - 1) >= 0 && (x - 1) >= 0)
            {
               map[y-1][x-1]++;
            }
           
            // vert und kroi
            if ((y + 1) < ySize)
            {
                map[y+1][x]++;
            }

            if ((y - 1) >= 0)
            {
               map[y-1][x]++;
            }

            if ((x + 1) < xSize)
            {
                map[y][x+1]++;
            }

            if ((x - 1) >= 0)
            {
               map[y][x-1]++;
            }

            return 1;
        }

    public:
        Board(){}

        void addRow(std::string line)
        {
            inputData.push_back(line);
        }

        void prepareData()
        {
            ySize = inputData.size();
            xSize = inputData[0].size();

            map = std::vector<std::vector<int>>(ySize, std::vector<int>(xSize, 0));

            for(int y = 0; y < ySize; y++)
            {
                std::string line = inputData[y];
                for(int x = 0; x < xSize; x++)
                {
                    map[y][x] = line[x] - '0';
                }
            }
        }

        int doStep()
        {
            int flashes = 0;
            std::vector<int> flashedX;
            std::vector<int> flashedY;

            // increase everything by 1
            for(int y = 0; y < ySize; y++)
            {
                std::string line = inputData[y];
                for(int x = 0; x < xSize; x++)
                {
                    map[y][x]++;
                }
            }

            //do flashes
            int localFlashes = 0;
            flashedMap = std::vector<std::vector<bool>>(ySize, std::vector<bool>(xSize, false));
            do
            {
                localFlashes = 0;
                for(int y = 0; y < ySize; y++)
                {
                    std::string line = inputData[y];
                    for(int x = 0; x < xSize; x++)
                    {
                        if ( map[y][x] > 9 && flashedMap[y][x] == false)
                        {
                            localFlashes+= doFlash(y, x);
                            flashedMap[y][x] = true;
                        } 
                    }
                }


                flashes += localFlashes;
            } while (localFlashes > 0);

            // reset flashed values
            for(int y = 0; y < ySize; y++)
            {
                for(int x = 0; x < xSize; x++)
                {
                    if (flashedMap[y][x] == true)
                    {
                        map[y][x] = 0;
                    }
                }
            }

            return flashes;
        }

        void print()
        {
            std::cout << "##################" << std::endl;
            for(int y = 0; y < ySize; y++)
            {
                for(int x = 0; x < xSize; x++)
                {
                   std::cout << "("<< map[y][x] << ")";
                }
                
                std::cout << std::endl;
            }
        }

};

int main()
{
    std::ifstream infile("input/day11");
    std::string input;
    int flashes = 0;
    Board board;

    while (infile >> input)
    {
        board.addRow(input);
    }

    board.prepareData();
    for (int i = 0; i < 100; i++)
    {
        flashes += board.doStep();
    }
   
    board.print();

    std::cout << "res = " << flashes << std::endl;

    return 0;
}