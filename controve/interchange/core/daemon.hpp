#ifndef __INTERCHANGE_DAEMON_H
#define __INTERCHANGE_DAEMON_H

#include <string>
#include <functional>
#include <vector>
#include "handler.hpp"
#include "datum.hpp"

/*
* @author Marcus Plutowski
*/
class Handler;
class Daemon {
    friend class Handler;
    friend class AsyncHandler;
public:
    Daemon(std::string uniqueName, Handler* parentHandler,
                            void (*useData)(std::string));
    Daemon();
    // uniqueName defines the Daemon for the Handler.

    void sendData(std::string, std::string protocolName);
    void sendData(std::string, std::string protocolName,
                                     std::string target);

    std::string getName();
private:
    void pullData();

    void (*useData)(std::string);

    Handler* handler;
    std::string name;
};

#endif //__INTERCHANGE_DAEMON_H
