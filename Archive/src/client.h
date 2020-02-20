#include <stdio.h>
#include <set>
#include <string>

using namespace std;

class Client{
    public:
    string ip;
    int port;

    set<string> sub_types;
    set<string> sub_originators;
    set<string> sub_orgs;
    Client(char *ip, int port);
};