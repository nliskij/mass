#ifndef __INTERCHANGE_HANDLER_H
#define __INTERCHANGE_HANDLER_H

#include <map>
#include <string>
#include <vector>
#include "ipaddr.hpp"
#include "datum.hpp"
#include "daemon.hpp"
#include "protocol.hpp"

/*
* @author Marcus Plutowski
*/
class Daemon;
class Protocol;
class Handler {
    friend class Daemon;
    friend class Protocol;

public:
    typedef std::map<std::string, std::vector<Datum> > dataBuffer;
    Handler(IPAddr targetAddress);
    Handler();
    virtual ~Handler();

    virtual void addDaemon(Daemon* newDaemon);
    virtual void removeDaemon(std::string name);

    virtual void addProtocol(Protocol* newProtocol);
    virtual void removeProtocol(std::string name);

    Daemon* getDaemon(std::string name);
    Protocol* getProtocol(std::string name);

protected:
    void stageData(Datum data, std::string protocolName);
    void retData(Datum data, std::string protocolName);

    std::vector<Protocol*> Protocols;
    std::vector<Daemon*> Daemons;

    dataBuffer receiveBuffer;
    dataBuffer sendBuffer;

    IPAddr target;
};

#endif //__INTERCHANGE_HANDLER_H
