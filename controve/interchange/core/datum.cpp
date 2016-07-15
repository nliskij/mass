#include "datum.hpp"

Datum::Datum()
{
    // Use null protocol rather than this or check for empty protocol
    data = "";
    targetName = "";
    protocolTransited = "";
}

Datum::Datum(std::string initData, std::string target, std::string protocol)
{
    data = initData;
    targetName = target;
    protocolTransited = protocol;
}

std::string Datum::getTarget() { return targetName; }

void Datum::timeStamp(Timer* timer) { timestamps.push_back(timer->getTime()); }
Timer::milliseconds Datum::getTimeStamp(int num) { return timestamps[num]; }

void Datum::setData(std::string newData) { data = newData; }
std::string Datum::getData() { return data; }

void Datum::setProtocol(std::string newProtocol)
{
    protocolTransited = newProtocol;
}
std::string Datum::getProtocol() { return protocolTransited; }
