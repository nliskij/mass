#include "async_handler.hpp"
#include <utility>

/*
*@author Marcus Plutowski
*/
AsyncHandler::AsyncHandler(IPAddr targetAddress, Timer* timer)
{
    daemonTickPeriod = 20;
    protocolTickPeriod = 10;
    this->target = targetAddress;
    this->timer = timer;

    lastProtocolTick = timer->getTime();
    lastDaemonTick = timer->getTime();

    runHandler = true;
    pthread_create(&clock, NULL, &AsyncHandler::threadedExecutor, NULL);
}
AsyncHandler::AsyncHandler(IPAddr targetAddress, Timer* timer, Timer::milliseconds daemonTickPeriod, Timer::milliseconds protocolTickPeriod)
{
    this->daemonTickPeriod = daemonTickPeriod;
    this->protocolTickPeriod = protocolTickPeriod;
    this->target = targetAddress;
    this->timer = timer;

    lastProtocolTick = timer->getTime();
    lastDaemonTick = timer->getTime();

    runHandler = true;
    pthread_create(&clock, NULL, &AsyncHandler::threadedExecutor, NULL);
}
AsyncHandler::~AsyncHandler(){
    runHandler = false;
    pthread_join(clock, NULL);
}
void* AsyncHandler::threadedExecutor(void* targetClass) {
    static_cast<AsyncHandler*>(targetClass)->regulateHandler();
    return nullptr;
}
void AsyncHandler::regulateHandler() {
    while (runHandler) {
        if ((timer->getTime() - lastDaemonTick) >= daemonTickPeriod) {
            this->tickDaemons();
        }
        if ((timer->getTime() - lastProtocolTick) >= protocolTickPeriod) {
            this->tickProtocols();
        }
    }
}
void AsyncHandler::tickDaemons() {
    for (auto daemon : Daemons) {
        daemon->pullData();
        /*TODO FINISH REGULATION */
    }
}
void AsyncHandler::tickProtocols()
{
    for (auto protocol : Protocols) {
        protocol->pullData();
        /*TODO FINISH REGULATION */
    }
}
