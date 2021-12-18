#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <regex>
#include <utility>

// Offset for easier calculation, due  every coordinate is positive
constexpr int OFFSET = 1000;

class Probe
{
    private:
        int xVelocity;
        int yVelocity;
        int x;
        int y;
        int yMax = INT32_MIN;

    public:
        Probe(int xVelocity, int yVelocity)
        {
            this->xVelocity = xVelocity;
            this->yVelocity = yVelocity;
            x = OFFSET;
            y = OFFSET;
        }

        void doStep()
        {
            x += xVelocity;
            y += yVelocity;

            // Due to drag, the probe's x velocity changes by 1 toward the value 0; that is, it decreases by 1 if it is greater than 0, increases by 1 if it is less than 0, or does not change if it is already 0.
            if (xVelocity > 0)
            {
                xVelocity--;
            }
            else if (xVelocity < 0)
            {
                xVelocity++;
            }

            // Due to gravity, the probe's y velocity decreases by 1.
            yVelocity--;

            if (yMax < y)
            {
                yMax = y;
            }
        }

        int getXVelocity()
        {
            return xVelocity;
        }
        
        int getYVelocity()
        {
            return yVelocity;
        }

        int getX()
        {
            return x;
        }

        int getY()
        {
            return y;
        }

        int getYMax()
        {
            return yMax - OFFSET;
        }

        void print()
        {
            std::cout << "Probe" << std::endl;
            std::cout << "pos x=" << (x - OFFSET) << " y=" << (y - OFFSET) << std::endl;
            std::cout << "velocity x=" << xVelocity << " y=" << yVelocity << std::endl;
        }
};

class Board
{
    private:
        std::pair<int, int> xTarget; 
        std::pair<int, int> yTarget;
        
        bool targetMissed(Probe probe)
        {

            if(xTarget.second < probe.getX())
            {
                return true;
            }
        
            if(yTarget.first > probe.getY())
            {
                return true;
            }
           
            return false;
        }


        bool targetHit(Probe probe)
        {
            if ((probe.getX() >= xTarget.first && probe.getX() <= xTarget.second) &&
                (probe.getY() >= yTarget.first && probe.getY() <= yTarget.second))
            {
                return true;
            }

            return false;
        }   

    public:
        Board(std::vector<int> &input)
        {
           xTarget.first = input[0] + OFFSET;
           xTarget.second = input[1] + OFFSET;
           yTarget.first = input[2] + OFFSET;
           yTarget.second = input[3] + OFFSET;
        }

    int fireProbe(int xVelocity, int yVeloctiy)
    {
        //TODo test
        Probe probe(xVelocity, yVeloctiy);

        do
        {
            probe.doStep();
        } while(targetHit(probe) != true && targetMissed(probe) != true);

        if (targetHit(probe))
        {
            return probe.getYMax();
        }

        return INT32_MIN;
    }
};


int main()
{
    std::ifstream infile("input/day17");
    std::string input;
    std::vector<int> coords;

    while (infile >> input)
    {
        if (input[0] == 'x' || input[0] == 'y')
        {
            int x = 0;
            std::string res;

            res = std::regex_replace(input, std::regex(std::string(1, input[0])), " ");
            res = std::regex_replace(res, std::regex("="), " ");
            res = std::regex_replace(res, std::regex("\\.\\."), " ");
            res = std::regex_replace(res, std::regex(","), " ");

            std::stringstream stream(res);
            while(stream >> x)
            {
                coords.push_back(x);
            }    
        }
    }

    Board board(coords);

    int result = INT32_MIN;
    int hitCount = 0;

    // brute force ;-)
    for (int x = -OFFSET; x < OFFSET; x++)
    {
        for (int y = -OFFSET; y < OFFSET; y++)
        {
            int res = board.fireProbe(x,y);

            if (res > result)
            {
                result = res;
            }

            if (res != INT32_MIN)
            {
                hitCount++;
            }
        }
    }
    

    std::cout << "result = " << result << std::endl;
    std::cout << "hitCount = " << hitCount << std::endl;

    return 0;
}