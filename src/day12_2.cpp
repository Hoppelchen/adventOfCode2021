#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <sstream>

class Board
{
    private:
        std::map<std::string, std::vector<std::string>> map;
    
    void addPath(std::string from, std::string to)
    {
        std::vector<std::string> destinations;
        if (map.find(from) != map.end())
        {
            destinations = map[from];
        }
        

        destinations.push_back(to);
        map[from] = destinations;
    }

    bool smallCaveVisitedTwice(std::map<std::string, int> visited)
    {
        for (const auto& [key, value] : visited)
        {
            if (key.compare("start") == 0)
            {
                continue;
            }

            if (value >= 2)
            {
                return true;
            }
        }

        return false;
    }

    int findPathRec(std::string currentPos,  std::map<std::string, int> visited)
    {
        if (currentPos.compare("end") == 0)
        {
            return 1;
        }
        else
        {
            std::vector<std::string> destinations = map[currentPos];
            int res = 0;

            if (currentPos[0] >= 'a')
            {
                visited[currentPos]++;
            }

            for(auto &dest : destinations)
            {
                if (smallCaveVisitedTwice(visited))
                {
                    if (visited[dest] < 1)
                    {
                        res += findPathRec(dest, visited);
                    }
                }
                else
                {
                    if (visited[dest] < 2)
                    {
                        res += findPathRec(dest, visited);
                    }
                }
            }

            return res;
        }
    }

    public:
        Board()
        {}

   

    void parsePath(std::string path)
    {
        std::stringstream stream(path);
        std::string input;
        std::vector<std::string> parts;

        //split by -
        while(std::getline(stream, input, '-'))
        {
            parts.push_back(input);
        }


        addPath(parts[0], parts[1]);
        addPath(parts[1], parts[0]);

    }

    int findPath()
    {
        std::map<std::string, int> visited;
        visited["start"] = 1;
        return findPathRec("start", visited);
    }

    void print()
    {
        for (const auto& [key, value] : map)
        {
            for (size_t i = 0; i < value.size(); i++)
            {
                std::cout << key << " -> " << value[i] << std::endl;
            }
            
        }
    }
};

int main()
{
    
    std::ifstream infile("input/day12");
    std::string input;
    Board board;

    while (infile >> input)
    {
        board.parsePath(input);
    }

    //board.print();

    std::cout << "find " << board.findPath() << std::endl;

    return 0;
}