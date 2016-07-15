#include "daemon.hpp"
#include "datum.hpp"
#include "handler.hpp"

/*
* @author Marcus Plutowski
*/
Daemon::Daemon(std::string uniqueName, Handler* parentHandler,
    void (*useData)(std::string)) {
    name = uniqueName;
    handler = parentHandler;
    this->useData = useData;
}
Daemon::Daemon(){}

std::string Daemon::getName(){
    return name;
}

void Daemon::sendData(std::string data, std::string protocolName) {
    Datum dat(data, this->name, protocolName);
    handler->stageData(dat, protocolName);
}
void Daemon::sendData(std::string data, std::string protocolName, std::string target) {
    Datum dat(data, target, protocolName);
    handler->stageData(dat, protocolName);
}

void Daemon::pullData() {
    for(Handler::dataBuffer::iterator buff = handler->receiveBuffer.begin(); buff != handler->receiveBuffer.end(); buff++){
        for(std::vector<Datum>::iterator itr = (buff->second).begin(); itr != (buff->second).end(); itr++){
            if(itr->getTarget() == this->name){
                useData(itr->getData());
                (buff->second).erase(itr);
            }
        }
    }
}
