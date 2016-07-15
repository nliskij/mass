#include "handler.hpp"

Handler::Handler(IPAddr targetAddress)
{
    this->target = targetAddress;
}
Handler::Handler(){
    target.setAddr(0, 0, 0, 0);
}
Handler::~Handler(){
}

void Handler::addDaemon(Daemon* newDaemon)
{
    Daemons.push_back(newDaemon);
}
void Handler::removeDaemon(std::string name)
{
    for(std::vector<Daemon*>::iterator itr = Daemons.begin(); itr != Daemons.end(); itr++){
        if((*itr)->getName() == name){
             Daemons.erase(itr);
        }
    }
}

void Handler::addProtocol(Protocol* newProtocol)
{
    Protocols.push_back(newProtocol);
}

void Handler::removeProtocol(std::string name)
{
    for(std::vector<Protocol*>::iterator itr = Protocols.begin(); itr != Protocols.end(); itr++){
        if((*itr)->getName() == name){
             Protocols.erase(itr);
        }
    }
}

void Handler::stageData(Datum data, std::string protocolName)
{
    receiveBuffer[protocolName].push_back(data);
}
void Handler::retData(Datum data, std::string protocolName)
{
    receiveBuffer[protocolName].push_back(data);
}

Daemon* Handler::getDaemon(std::string name){
    for(Daemon* daemon : this->Daemons){
        if(daemon->getName() == name){ return daemon; }
    }
    return new Daemon();
}
Protocol* Handler::getProtocol(std::string name){
    for(Protocol* protocol : this->Protocols){
        if(protocol->getName() == name){ return protocol; }
    }
    return nullptr;
}
