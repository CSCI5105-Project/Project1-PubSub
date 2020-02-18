#include <stdio.h>
#include <vector>
#include <string>

using namespace std;

class Client{
    public:
    int ip;
    int port;

    vector<string> sub_types;
    vector<string> sub_originators;
    vector<string> sub_orgs;
    Client(char *ip, int port);
};