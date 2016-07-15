#include "protocol.hpp"
#include <string>

class NullProtocol : Protocol{
public:
    NullProtocol(Handler* handler);
    void ProtocolFactory(std::string name, Handler* handler, int port) override;
    std::string getName() override;
private:
    void pullData() override;
};
