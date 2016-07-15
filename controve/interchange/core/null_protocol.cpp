#include "null_protocol.hpp"
#include <iostream>
#include <typeinfo>

NullProtocol::NullProtocol(Handler* handler){
    this->ProtocolFactory("", handler, -1);
}
void NullProtocol::ProtocolFactory(std::string name, Handler* handler, int port){//, Handler* handler){
    this->port = port;
    this->name = name;
    this->handler = handler;
    handler->addProtocol(this);
    std::cout<<typeid(this).name();
}
void NullProtocol::pullData() {
    /*for(Handler::dataBuffer::iterator buff = handler->receiveBuffer.begin(); buff != handler->receiveBuffer.end(); buff++){
        for(std::vector<Datum>::iterator itr = (buff->second).begin(); itr != (buff->second).end(); itr++){
            if(itr->getTarget() == this->name){
                (buff->second).erase(itr);
            }
        }
    }*/
}
std::string NullProtocol::getName(){
    return "";
}
