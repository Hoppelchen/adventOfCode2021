#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <bitset>


constexpr int LITERAL = 4;

class Packet
{
    private:
        std::vector<std::bitset<4>> hexData;

        int getBitsFrom(int startIndex, int length)
        {
            int retVal = 0;
            for (int i = 0; i < length; i++)
            {
                std::bitset<4> tmp = hexData[(startIndex+i)/4];
                retVal |=  (tmp[3 - ((startIndex+i) % 4)] & 0x1) << (length - i - 1);
            }

            return retVal;
        }

        int getLength()
        {
            return hexData.size() * 4;
        }
    public:
        Packet(std::string input)
        {
            for (size_t i = 0; i < input.size(); i++)
            {
                hexData.push_back(std::bitset<4>(stoi(input.substr(i, 1), NULL, 16)));
            }
        }

        Packet(std::vector<std::bitset<4>> input)
        {
            hexData = input;
            std::cout << "New Packet Version: " << getVersion() << " type:" << getType() << std::endl;
        }

        int getVersion()
        {
            return getBitsFrom(0, 3);
        }

        int getType()
        {
            return getBitsFrom(3, 3);
        }

        std::vector<int> getDataAsLiteralValue()
        {
            // TODO guard literal
            std::vector<int> ret;
            for (int i = 6; i  < getLength(); i+=5)
            {
                ret.push_back(getBitsFrom(i+1, 4));

                // last string literal
                if (getBitsFrom(i, 1) == 0)
                {
                    break;
                }
            }

            return ret;
        }
};

class PacketParser
{
    private:
        std::vector<std::bitset<4>> hexData;
        std::vector<Packet> packets;
        int getBitsFromAsInt(int startIndex, int length)
        {
            int retVal = 0;
            for (int i = 0; i < length; i++)
            {
                std::bitset<4> tmp = hexData[(startIndex+i)/4];
                retVal |=  (tmp[3 - ((startIndex+i) % 4)] & 0x1) << (length - i - 1);
            }

            return retVal;
        }

        std::vector<std::bitset<4>> getBitsFromAsVector(int startIndex, int length)
        {
            std::vector<std::bitset<4>> ret;
            int index = 0;
            std::bitset<4> newVal(0);
            
            for (int i = 0; i < length; i++)
            {
                std::bitset<4> tmp = hexData[(startIndex+i)/4];

                newVal[3 - (index % 4)] = tmp[3 - ((startIndex+i) % 4)];
                index++;
                if (index % 4 == 0)
                {
                    ret.push_back(newVal);
                    newVal = std::bitset<4>(0);
                }
            }
            
            if (index%4 != 0)
            {
                ret.push_back(newVal);
            }
            
            return ret;
        }

        int getLength()
        {
            return hexData.size() * 4;
        }

        int getLiteralLenOfValues(int offset)
        {
            int num = 0;
            for (int i = offset + 6; i  < getLength(); i+=5)
            {
                num++;
                // last string literal
                if (getBitsFromAsInt(i, 1) == 0)
                {
                    return num*5;
                }
            }

            return 0;
        }

        int getLiteralOffsetOfValues(int offset)
        {
            for (int i = offset + 6; i  < getLength(); i+=5)
            {
                // last string literal
                if (getBitsFromAsInt(i, 1) == 0)
                {
                    return i + 5;
                }
            }

            return 0;
        }

        int getVersion(int offset)
        {
            return getBitsFromAsInt(offset, 3);
        }

        int getType(int offset)
        {
            return getBitsFromAsInt(offset + 3, 3);
        }

        int getLengthTypeId(int offset)
        {
            return getBitsFromAsInt(offset + 6, 3);
        }

        int get15Bitlength(int offset)
        {
            return getBitsFromAsInt(offset + 7, 15);
        }

        int getStartSubPackage15BitHeader(int offset)
        {
            return offset + 7 + 15;
        }

        int get11Bitlength(int offset)
        {
            return getBitsFromAsInt(offset + 7, 11);
        }

        int getStartSubPackage11BitHeader(int offset)
        {
            return offset + 7 + 11;
        }

    public:
        
        PacketParser(std::string input)
        {
            for (size_t i = 0; i < input.size(); i++)
            {
                hexData.push_back(std::bitset<4>(stoi(input.substr(i, 1), NULL, 16)));
            }
        }

        int parseRec(int startIndex)
        {
            int lastIndex = startIndex;

            if ((getLength() - startIndex ) < 8)
            {
                return startIndex;
            }

            // getPackageType
            if (getType(startIndex) == LITERAL)
            {
                //int len =  getLiteralLenOfValues(startIndex);
                lastIndex = getLiteralOffsetOfValues(startIndex);
                
                packets.push_back(Packet(getBitsFromAsVector(startIndex, lastIndex - startIndex)));

                if ((getLength() - (lastIndex)) < 8)
                {
                    return lastIndex;
                }

                return parseRec(lastIndex);
            }
            else
            {
                if (getLengthTypeId(startIndex) == 0)
                {
                    // 15 bit number -> num of subpackages
                    packets.push_back(Packet(getBitsFromAsVector(startIndex, 7 + 15)));
                    int tmp = parseRec(getStartSubPackage15BitHeader(startIndex));

                    if ((getLength() - (tmp)) < 8)
                    {
                        return tmp;
                    }

                    return getLength(); 
                }
                else
                {
                   // 11 bit number -> num of subpackages
                    packets.push_back(Packet(getBitsFromAsVector(startIndex, 7 + 11)));
                    int tmp = parseRec(getStartSubPackage11BitHeader(startIndex));

                    if ((getLength() - (tmp)) < 8)
                    {
                        return tmp;
                    }

                    return getLength(); 
                    //return parseRec(startIndex + lastIndex);
                }

                return startIndex;
            }

            
        }

        void parse()
        {
            parseRec(0);
        }

       
        int getResult()
        {
            int ret = 0;

            for(auto &packet : packets)
            {
                ret += packet.getVersion();
            }

            return ret;
        }

        void print()
        {
            for (int i = 0; i < getLength(); i++)
            {
                std::bitset<4> tmp = hexData[i/4];
                std::cout << tmp[3 - i % 4];
            }

            std::cout << std::endl;
        }

};



int main()
{
    std::ifstream infile("input/day16");
    std::string input;
    

    std::getline(infile, input);
    PacketParser packetparser(input);
    
    //packetparser.print();
    
    packetparser.parse();
  
    int result = packetparser.getResult();

    std::cout << "result = " << result << std::endl;

    return 0;
}