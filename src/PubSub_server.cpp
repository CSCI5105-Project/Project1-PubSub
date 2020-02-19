/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "PubSub.h"
#include "client.h"
#include "stringTokenizer.h"
#include <stdio.h>
#include <cstring>
#include <vector>
#include <arpa/inet.h>
#include <algorithm>
#include <iostream>
#include <netdb.h>

using namespace std;

static const int reg_port = 5105;

vector<Client> clients;
vector<int> sockets;
vector<sockaddr_in> sockaddr;


vector<Client>::iterator seek_Client(string IP, int Port){
	string ip;
	inet_pton(AF_INET, IP.c_str(), &ip);
	auto it = clients.begin();
	for (; it != clients.end(); ++it) {
		if (it->ip == ip && it->port == Port) {
			return it;
		}
	}
	return it;
}

bool_t *
join_1_svc(char *IP, int Port,  struct svc_req *rqstp)
{
	static bool_t  result;

	if(clients.size()>=MAXCLIENT){
		fprintf(stderr,"Cannot add more clients!\n");
		result = 1;
	}
	else if(seek_Client(IP,Port) != clients.end()){
		fprintf(stderr,"Client (%s,%d) has already joined to the server!\n",IP,Port);
		result = 1;
	}
	else{
		Client c(IP,Port);
		clients.push_back(c);
		int sock;
		if((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
			perror("cannot create socket");
			result = 1;
		}
		else{
			sockets.push_back(sock);			
			struct hostent *ht;
			struct sockaddr_in addr;
			ht = gethostbyname(IP);
			if(!ht){
				fprintf(stderr, "could not obtain address of %s\n", IP);
				result = 1;
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
	}	
	return &result;
}

bool_t *
leave_1_svc(char *IP, int Port,  struct svc_req *rqstp)
{
	static bool_t  result;
	auto it = seek_Client(IP,Port);
	if(it != clients.end()){
		clients.erase(it);
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
	string s;

	auto it = seek_Client(IP,Port);
	if (it != clients.end()) {
		s = token.GetNext();
		if (s.size() > 0) it->sub_types.insert(s);
		fprintf(stdout,"subscribe() %s successfully.\n", s.c_str());

		s = token.GetNext();
		if (s.size() > 0) it->sub_originators.insert(s);
		fprintf(stdout,"subscribe() %s successfully.\n", s.c_str());

		s = token.GetNext();
		if (s.size() > 0) it->sub_orgs.insert(s);
		fprintf(stdout,"subscribe() %s successfully.\n", s.c_str());

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

	auto it = seek_Client(IP,Port);
	if (it != clients.end()) {
		Client &c = *it;

		s = token.GetNext();
		c.sub_types.erase(s);
		fprintf(stdout,"unsubscribe() %s successfully.\n", s.c_str());

		s = token.GetNext();
		c.sub_originators.erase(s);
		fprintf(stdout,"unsubscribe() %s successfully.\n", s.c_str());
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

	vector< int > targetClinets;

	int i = 0;
	for (auto it = clients.begin(); it != clients.end(); ++it, ++i) {
		bool isTargetClinet = false;
		isTargetClinet |= it->sub_types.find(type) != it->sub_types.end();
		isTargetClinet |= it->sub_originators.find(type) != it->sub_originators.end();
		isTargetClinet |= it->sub_orgs.find(type) != it->sub_orgs.end();
		if (isTargetClinet) targetClinets.push_back(i);
	}

	int sockfd;
	if (sockfd = socket(AF_INET, SOCK_DGRAM, 0) < 0) {
		perror("cannot create socket");
		return 0;
	}
	struct sockaddr_in serv_addr, client_addr;

	for (auto it = targetClinets.begin(); it != targetClinets.end(); ++it) {
		// sendto(*it, Article, strlen(Article), 0, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
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

int register

