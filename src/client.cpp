#include "client.h"
#include <arpa/inet.h>

Client::Client(char *ip_, int port_){
    this->port = port_;
    inet_pton(AF_INET,ip_,&this->ip);
}