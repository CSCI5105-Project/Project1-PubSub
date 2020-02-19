/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "PubSub.h"
#include "client.h"
#include "stringTokenizer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>

#include <cstring>
#include <vector>
 
#include <unistd.h>
#include <string.h>

#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <netdb.h>

using namespace std;

// static const int reg_port = 5105;
// static const int groupserver_port = 5107;
// static const char *register_server_name = "127.0.0.1";

vector<Client> clients;
vector<int> sockets;
vector<sockaddr_in> sockaddr;

set<string> legalTypes = {"Sports", "Lifestyle", "Entertainment", "Business", "Technology", "Science", "Politics", "Health"};


int seek_Client(string IP, int Port){
	//string ip;
	//inet_pton(AF_INET, IP.c_str(), &ip);
	//cout<<clients.size()<<endl<<flush;
	for (int i = 0; i < clients.size(); ++i) {
		if (clients[i].ip == IP && clients[i].port == Port) {
			return i;
		}
	}
	return -1;
}

// char* getIP()
// {
//  	static char ip_address[15];
//     int fd;
//     struct ifreq ifr;
     
//     /*AF_INET - to define network interface IPv4*/
//     /*Creating soket for it.*/
//     fd = socket(AF_INET, SOCK_DGRAM, 0);
     
//     /*AF_INET - to define IPv4 Address type.*/
//     ifr.ifr_addr.sa_family = AF_INET;
     
//     /*eth0 - define the ifr_name - port name
//     where network attached.*/
//     memcpy(ifr.ifr_name, "eno1", IFNAMSIZ-1);
     
//     /*Accessing network interface information by
//     passing address using ioctl.*/
//     ioctl(fd, SIOCGIFADDR, &ifr);
//     /*closing fd*/
//     close(fd);
     
//     /*Extract IP Address*/
//     strcpy(ip_address,inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));

// 	return ip_address;
// }

bool_t *
join_1_svc(char *IP, int Port,  struct svc_req *rqstp)
{
	static bool_t  result;
	
	if(clients.size()>=MAXCLIENT){
		fprintf(stderr,"Cannot add more clients!\n");
		result = 0;
	}
	else if(seek_Client(IP,Port) != -1){
		fprintf(stderr,"Client (%s,%d) has already joined to the server!\n",IP,Port);
		result = 0;
	}
	else{
		Client c(IP,Port);
		clients.push_back(c);
		int sock;

		if((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
			perror("cannot create socket");
			result = 0;
		}
		else{
			sockets.push_back(sock);			
			struct hostent *ht;
			struct sockaddr_in addr;
			ht = gethostbyname(IP);
			if(!ht){
				fprintf(stderr, "could not obtain address of %s\n", IP);
				result = 0;
			}
			else{
				bzero(&addr,sizeof(addr));
				addr.sin_family = AF_INET;
				addr.sin_port = htons(Port);
				memcpy((void *)&addr.sin_addr,ht->h_addr_list[0],ht->h_length);
				sockaddr.push_back(addr);
			}
		}
		fprintf(stdout,"Client (%s,%d) Join successfully!!\n",IP,Port);
		result = 1;
		cout<<"clients[0] = "<<clients[0].ip<<endl<<flush;
	}	
	return &result;
}

bool_t *
leave_1_svc(char *IP, int Port,  struct svc_req *rqstp)
{
	static bool_t  result;
	int id = seek_Client(IP,Port);
	if(id != -1){
		clients.erase(clients.begin() + id);
		printf("Client (%s,%d) leaves group server successfully!!\n",IP,Port);
	}
	else{
		fprintf(stderr,"Cannot find Client (%s,%d)!!\n",IP,Port);
		result = 1;
	}
	return &result;
}

bool_t *
subscribe_1_svc(char *IP, int Port, char *Article,  struct svc_req *rqstp)
{
	static bool_t  result;

	CStringTokenizer token;
	token.Split(Article, ";"); 
	string type, originators, orgs, content;
	type = token.GetNext();
	originators = token.GetNext();
	orgs = token.GetNext();
	content = token.GetNext();

	int id = seek_Client(IP,Port);
	if (id != -1) {
		if (content.size() > 0) {
			fprintf(stdout,"Client %d subscribe() failed: The arcitle content is not empty.\n", id);
			result = false;
			return &result;
		}

		if (type.size() == 0 && originators.size() == 0 && orgs.size() == 0) {
			fprintf(stdout,"Client %d subscribe() failed: The first three fields are empty.\n", id);
			result = false;
			return &result;
		}

		if (type.size() > 0)  {
			if (legalTypes.find(type) != legalTypes.end()) {
				clients[id].sub_types.insert(type);
				fprintf(stdout,"Client %d subscribe() type %s successfully.\n", id, type.c_str());
			} else {
				fprintf(stdout,"Client %d subscribe() %s failed: Illegal type.\n", id, type.c_str());
			}
		}

		if (originators.size() > 0) {
			clients[id].sub_originators.insert(originators);
			fprintf(stdout,"Client %d subscribe() originators %s successfully.\n", id, originators.c_str());
		}

		if (orgs.size() > 0) {
			clients[id].sub_orgs.insert(orgs);
			fprintf(stdout,"Client %d subscribe() orgs %s successfully.\n", id, orgs.c_str());
		}

		result = true;
	} else {
		fprintf(stdout, "subscribe() failed: cannot find Client (%s, %d)\n", IP, Port);
		result = false;
	}
	return &result;
}

bool_t *
unsubscribe_1_svc(char *IP, int Port, char *Article,  struct svc_req *rqstp)
{
	static bool_t  result;

	CStringTokenizer token;
	token.Split(Article, ";");
	string s;

	int id = seek_Client(IP,Port);
	if (id != -1) {
		Client &c = clients[id];

		s = token.GetNext();
		if (s.size() > 0) {
			c.sub_types.erase(s);
			fprintf(stdout,"unsubscribe() %s successfully.\n", s.c_str());
		}

		s = token.GetNext();
		if (s.size() > 0) {
			c.sub_originators.erase(s);
			fprintf(stdout,"unsubscribe() %s successfully.\n", s.c_str());
		}

		s = token.GetNext();
		if (s.size() > 0) {
			c.sub_originators.erase(s);
			fprintf(stdout,"unsubscribe() %s successfully.\n", s.c_str());
		}
	} else {
		fprintf(stdout, "unsubscribe() failed: cannot find Client (%s, %d)\n", IP, Port);
		result = false;	
	}

	return &result;
}

bool_t *
publish_1_svc(char *Article, char *IP, int Port,  struct svc_req *rqstp)
{
	static bool_t  result;

	CStringTokenizer token;
	token.Split(Article, ";");

	string type = token.GetNext();
	string originators = token.GetNext();
	string orgs = token.GetNext();
	string content = token.GetNext();

	if ((type.size() > 0) && (legalTypes.find(type) == legalTypes.end())) {
		cout << "Publish failed: The type " << type << " is illegal!" << endl << flush;
		result = false;
		return &result;
	}

	if (type.size() == 0 && originators.size() == 0 && orgs.size() == 0) {
		cout << "Publish failed: There first three fields are empty" << endl << flush;
		result = false;
		return &result;
	}

	if (content.size() == 0) {
		cout << "Publish failed: Empty article content" << endl << flush;
		result = false;
		return &result;
	}

	vector< int > targetClinets;

	int i = 0;
	for (auto it = clients.begin(); it != clients.end(); ++it, ++i) {
		bool isTargetClinet = false;
		isTargetClinet |= it->sub_types.find(type) != it->sub_types.end();
		isTargetClinet |= it->sub_originators.find(originators) != it->sub_originators.end();
		isTargetClinet |= it->sub_orgs.find(orgs) != it->sub_orgs.end();
		if (isTargetClinet) targetClinets.push_back(i);
	}

	int sockfd;
	if (sockfd = socket(AF_INET, SOCK_DGRAM, 0) < 0) {
		perror("cannot create socket");
		return 0;
	}
	struct sockaddr_in serv_addr, client_addr;

	cout << "server publishing artible is: " << Article <<  endl << flush;


	for (auto it = targetClinets.begin(); it != targetClinets.end(); ++it) {
		sendto(sockets[*it], Article, strlen(Article), 0, (struct sockaddr *)&sockaddr[*it], sizeof(serv_addr));
	}

	return &result;
}

bool_t *
ping_1_svc(struct svc_req *rqstp)
{
	static bool_t  result;

	/*
	 * insert server code here
	 */
	fprintf(stdout,"Successful Ping.\n");
	result = 1;
	return &result;
}


