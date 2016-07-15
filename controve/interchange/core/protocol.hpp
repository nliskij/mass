#ifndef _INTERCHANGE_PROTOCOL_H
#define _INTERCHANGE_PROTOCOL_H

#include "handler.hpp"
#include <string>

/*
* @author Marcus Plutowski
*/

class Handler;

class Protocol {
friend class Handler;
friend class AsyncHandler;
public:
    virtual void ProtocolFactory(std::string name, Handler* handler, int port) = 0;

    virtual std::string getName() = 0;

protected:
    std::string name;
    int port;
    Handler* handler;

    virtual void pullData() = 0;
};

#endif
