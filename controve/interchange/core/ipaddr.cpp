#include "ipaddr.hpp"
#include <sstream>
#include <algorithm>
#include <string>

IPAddr::IPAddr(int blockA, int blockB, int blockC, int blockD)
{
    this->setAddr(blockA, blockB, blockC, blockD);
}
IPAddr::IPAddr(std::string address) { this->setAddr(address); }
IPAddr::IPAddr(){this->setAddr("000000000000");}

void IPAddr::setAddr(int blockA, int blockB, int blockC, int blockD)
{
    address[0] = blockA;
    address[1] = blockB;
    address[2] = blockC;
    address[3] = blockD;
}
void IPAddr::setAddr(std::string addressString)
{
    std::string buf = "";

    for (int i = 0; i < 4; i++) {
        for (int x = 0; x < 3; x++) {
            buf += addressString[3 * i + x];
        }
        address[i] = std::stoi(buf);
        buf = "";
    }
}

std::string IPAddr::getIPString()
{

    std::string output = "";

    for (int i = 0; i < 4; i++) {
        if (this->getBlock(i) < 10) {
            output += "0";
        }
        if (this->getBlock(i) < 100) {
            output += "0";
        }
        output += std::to_string(this->getBlock(i));
    }

    return output;
}
int IPAddr::getBlock(int blockNo)
{
    return address[std::min(3, std::max(blockNo, 0))];
}
