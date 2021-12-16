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
        int subPackages = 0;

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

        int getLengthTypeId()
        {
            return getBitsFromAsInt(6, 3);
        }

        int get15Bitlength()
        {
            int num = 0;
            for (int i =  6; i  < getLength(); i+=5)
            {
                num++;
                // last string literal
                if (getBitsFromAsInt(i, 1) == 0)
                {
                    return num+1;
                }
            }

            return 0;
        }

        int get11Bitlength()
        {
            return getBitsFromAsInt(7, 11);
        }

        void parse()
        {
            
            if (getType() != LITERAL)
            {
                std::cout << getLengthTypeId() << std::endl;
                if (getLengthTypeId() == 0)
                {
                    print();
                    subPackages = get15Bitlength();
                }
                else
                {
                    subPackages = get11Bitlength();
                }

                std::cout << "subpackages: " << subPackages << std::endl;
            }
            else
            {
                std::cout << "value: " << getValue() << std::endl;
            }
        }

    public:
        Packet(std::string input)
        {
            for (size_t i = 0; i < input.size(); i++)
            {
                hexData.push_back(std::bitset<4>(stoi(input.substr(i, 1), NULL, 16)));
            }
            std::cout << "New Packet Version: " << getVersion() << " type:" << getType() << std::endl;

            parse();
        }

        Packet(std::vector<std::bitset<4>> input)
        {
            hexData = input;
            std::cout << "New Packet Version: " << getVersion() << " type:" << getType() << std::endl;

            parse();
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

        int getValue()
        {
            int value = 0;
            std::vector<int> val = getDataAsLiteralValue();
            for(size_t i = 0; i < val.size(); i++)
            {
                value |= val[i] << (i * 4);
            }

            return value;
        }

        int getNumSubpackages()
        {
            return subPackages;
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
                // getLength
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

        int64_t parseMath()
        {
            int index = 0;
            return parseMath(index);
        }

        int64_t parseMath(int &startIndex)
        {
            Packet &current = packets[startIndex];
            int type = current.getType();

            switch (type)
            {
                case 0:
                {
                    std::cout << "sum" << std::endl;
                    int64_t sum = 0;

                    startIndex++;
                    for (int i = 1; i <= current.getNumSubpackages(); i++)
                    {
                        sum += parseMath(startIndex);
                    }



                    return sum;
                }
                
                case 1:
                {
                    std::cout << "product" << std::endl;
                    int64_t prod = 1;

                    startIndex++;
                    for (int i = 1; i <= current.getNumSubpackages(); i++)
                    {
                        prod *= parseMath(startIndex);
                    }

                    return prod;
                }

                case 2:
                    {
                        std::cout << "min" << std::endl;
                        int64_t min = INT32_MAX;
                        startIndex++;
                        for (int i = 1; i <= current.getNumSubpackages(); i++)
                        {
                           int64_t val = parseMath(startIndex);
                           if (val < min)
                           {
                               min = val;
                           }
                        }

                        return min;                
                    }
                case 3:
                    {
                        std::cout << "max" << std::endl;
                        int64_t max = 0;
                        startIndex++;
                        for (int i = 1; i <= current.getNumSubpackages(); i++)
                        {
                            int64_t val = parseMath(startIndex);
                            if (val > max)
                            {
                                max = val;
                            }
                        }

                        return max; 
            
                    }
                case 5:
                    {
                        std::cout << "greater" << std::endl;
                        int64_t a[2];
                        startIndex++;
                        for (int i = 0; i < current.getNumSubpackages(); i++)
                        {
                            a[i] = parseMath(startIndex);
                        }

                        return (a[0] > a[1]);  
                    }
                case 6:
                    {
                        std::cout << "less" << std::endl;
                        int64_t a[2];
                        startIndex++;
                        for (int i = 0; i < current.getNumSubpackages(); i++)
                        {
                            a[i] = parseMath(startIndex);
                        }

                        return (a[0] < a[1]) ;
                
                    }
                case 7:
                    {
                        std::cout << "eqal" << std::endl;
                        int64_t a[2];
                        startIndex++;
                        for (int i = 0; i < current.getNumSubpackages(); i++)
                        {
                            a[i] = parseMath(startIndex);
                        }

                        return (a[0] == a[1]);  
                    }
                   
                default:
                    std::cout << "value: " << current.getValue() << std::endl;
                    startIndex++;
                    return current.getValue();
            }

            return 0;
        }
};



int main()
{
    std::ifstream infile("input/day16");
    std::string input;
    

    std::getline(infile, input);
    PacketParser packetparser(input);
    
    packetparser.print();
    
    packetparser.parse();
  
    //int result = packetparser.getResult();

    int64_t result = packetparser.parseMath();

    std::cout << "result = " << result << std::endl;

    return 0;
}