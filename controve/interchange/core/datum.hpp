#ifndef __INTERCHANGE_DATUM_H
#define __INTERCHANGE_DATUM_H

#include <string>
#include "timer.hpp"
#include <vector>

class Datum {
public:
    Datum();
    Datum(std::string initData, std::string target, std::string protocol);

    void timeStamp(Timer* timer);
    Timer::milliseconds getTimeStamp(int num);

    void setData(std::string newData);
    std::string getData();

    std::string getTarget();

    void setProtocol(std::string protocolName);
    std::string getProtocol();

private:
    std::string data;
    std::vector<Timer::milliseconds> timestamps;

    std::string protocolTransited;
    std::string targetName;
};

#endif
