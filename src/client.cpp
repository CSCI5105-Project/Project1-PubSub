#include "client.h"
#include <arpa/inet.h>

Client::Client(char *ip_, int port_){
    this->port = port_;
    char tmp[20];
    inet_pton(AF_INET,ip_,&tmp);
    ip = tmp;

    sub_types.clear();
    sub_originators.clear();
    sub_orgs.clear();
}