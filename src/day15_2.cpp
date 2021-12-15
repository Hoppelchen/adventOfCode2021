#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>

constexpr int MULTIPLICATOR = 5;

class Point
{
    private:
        std::pair<int,int> position;
        int costs;
        int distance = INT_MAX;
    public:
        Point(){}

        Point(int y, int x, int costs)
        {
            position = std::pair<int, int>(y, x);
            this->costs = costs;
        }

        std::pair<int, int> getPosition()
        {
            return position;
        }

        int getCosts()
        {
            return costs;
        }

        void setDistance(int distance)
        {
            this->distance = distance;
        }

        int getDistance()
        {
            return distance;
        }

        void print()
        {
            std::cout << "y=" << position.first << " y=" << position.second << " cost=" << costs << std::endl;
        }
};

class Dijkstra
{
    private:
        std::vector<std::string> inputData;
        std::vector<std::vector<Point>> points;
        std::vector<std::pair<int, int>> pointsToCheck;
        int xSizeInput;
        int ySizeInput;
        int xSize;
        int ySize;

        Point& getStart()
        {
            return points[0][0];
        }

        Point& getTarget()
        {
            return points[ySize - 1][xSize - 1];
        }
        
        Point& getShortestDistancePoint()
        {
            std::pair<int, int> pos = pointsToCheck.front();

            for(size_t i = 1; i < pointsToCheck.size(); i++)
            {
                if (points[pos.first][pos.second].getDistance() > points[pointsToCheck[i].first][pointsToCheck[i].second].getDistance())
                {
                    pos = pointsToCheck[i];
                }
            }

            return points[pos.first][pos.second];
        }

        std::vector<std::pair<int,int>> getLinkedNodes(Point& point)
        {
            std::vector<std::pair<int,int>> ret;
            std::pair<int,int> pos = point.getPosition();

            if(pos.first - 1 > 0)
            {
                std::pair<int,int> check(pos.first - 1, pos.second);
                if (std::find(pointsToCheck.begin(), pointsToCheck.end(), check) != pointsToCheck.end())
                {
                    ret.push_back(check);
                }
            }
            
            if(pos.first + 1 < ySize)
            {
                std::pair<int,int> check(pos.first + 1, pos.second);
                if (std::find(pointsToCheck.begin(), pointsToCheck.end(), check) != pointsToCheck.end())
                {
                    ret.push_back(check);
                }
            }

            if(pos.second - 1 > 0)
            {
                std::pair<int,int> check(pos.first, pos.second - 1);
                if (std::find(pointsToCheck.begin(), pointsToCheck.end(), check) != pointsToCheck.end())
                {
                    ret.push_back(check);
                }
            }
            
            if(pos.second + 1 < xSize)
            {
                std::pair<int,int> check(pos.first, pos.second + 1);
                if (std::find(pointsToCheck.begin(), pointsToCheck.end(), check) != pointsToCheck.end())
                {
                    ret.push_back(check);
                }
            }

            return ret;
        }

    public:
        Dijkstra()
        {}

        void addInputData(std::string input)
        {
            inputData.push_back(input);
        }

        void buildData()
        {
            ySizeInput = inputData.size();
            xSizeInput = inputData[0].size();

            ySize = ySizeInput * MULTIPLICATOR;
            xSize = xSizeInput * MULTIPLICATOR;

            std::cout << "yMax= " << ySize << " xMax= " << xSize << std::endl;

            for(int y = 0; y < ySize; y++)
            {
                int yAdd = y / ySizeInput;
                int yIndex = y % ySizeInput;

                std::vector<Point> dataLine;
                std::string input = inputData[yIndex];
                for(int x = 0; x < xSize; x++)
                {
                    int xAdd = x / xSizeInput;
                    int xIndex = x % ySizeInput;

                    int costs = (input[xIndex] - '0') + xAdd + yAdd;
                    if (costs > 9)
                    {
                        costs -= 9;
                    }

                    Point point(y, x, costs);
                    dataLine.push_back(point);
                    pointsToCheck.push_back(point.getPosition());
                }

                 points.push_back(dataLine);
            }
        }

        void print()
        {
            std::cout << "ptint" << std::endl;
            for(int y = 0; y < ySize; y++)
            {
                for(int x = 0; x < xSize; x++)
                {
                    std::cout << (points[y][x]).getCosts();
                }

                std::cout << std::endl;
            }
        }

        void printDistances()
        {
            for(int y = 0; y < ySize; y++)
            {
                std::cout << (y) << " ";
                for(int x = 0; x < xSize; x++)
                {
                    if ((points[y][x]).getDistance() == INT_MAX)
                    {
                        std::cout << "(.) ";
                    }
                    else
                    {
                        std::cout << "(" <<  (points[y][x]).getDistance() << ") ";
                    }
                    
                }

                std::cout << std::endl;
            }
        }

        int calculateDistance()
        {
            Point& start = getStart();
            start.setDistance(0);

            while(pointsToCheck.size() > 0)
            {
                Point& nodeToCheck = getShortestDistancePoint();

                for(std::pair<int, int> coords : getLinkedNodes(nodeToCheck))
                {
                    Point& point = points[coords.first][coords.second];

                    int newDistance = nodeToCheck.getDistance() + point.getCosts();
                    if (newDistance < point.getDistance())
                    {
                        point.setDistance(newDistance);
                    }
                }

                // point checked, remove from list
                pointsToCheck.erase(std::remove(pointsToCheck.begin(), pointsToCheck.end(), nodeToCheck.getPosition()), pointsToCheck.end());

                if (pointsToCheck.size() % 1000 == 0)
                {
                    std::cout << "Points to check: " << pointsToCheck.size() << std::endl;
                }
            }

            return getTarget().getDistance();
        }
    
};

int main()
{
   
    std::ifstream infile("input/day15");
    std::string input;
    Dijkstra dijkstra;

    while (infile >> input)
    {
        dijkstra.addInputData(input);
    }

    dijkstra.buildData();
    //dijkstra.print();

    int result = dijkstra.calculateDistance();

    //dijkstra.printDistances();

    std::cout << "result = " << result << std::endl;

    return 0;
}