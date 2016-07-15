#ifndef __INTERCHANGE_IP_ADDR_H
#define __INTERCHANGE_IP_ADDR_H

#include <string>
#include <sstream>

class IPAddr {
public:
    IPAddr(int blockA, int blockB, int blockC, int blockD);
    IPAddr(std::string addressString); // MSB first in the string. Always include
    IPAddr();
    // 3 characters. 192168001104 =
    // 192.168.1.104

    void setAddr(int blockA, int blockB, int blockC, int blockD);
    void setAddr(std::string addressString);

    std::string getIPString();
    int getBlock(int blockNo);

private:
    short address[4];
};

#endif // __INTERCHANGE_IP_ADDR_H
