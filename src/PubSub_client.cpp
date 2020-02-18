/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "PubSub.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
 
#include <unistd.h>
#include <string.h>

#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>

using namespace std;

struct ClientAddress {
	char ip[15];
	int port;
};

vector<ClientAddress> clients;

char* getIP()
{
 	char ip_address[15];
    int fd;
    struct ifreq ifr;
     
    /*AF_INET - to define network interface IPv4*/
    /*Creating soket for it.*/
    fd = socket(AF_INET, SOCK_DGRAM, 0);
     
    /*AF_INET - to define IPv4 Address type.*/
    ifr.ifr_addr.sa_family = AF_INET;
     
    /*eth0 - define the ifr_name - port name
    where network attached.*/
    memcpy(ifr.ifr_name, "eno1", IFNAMSIZ-1);
     
    /*Accessing network interface information by
    passing address using ioctl.*/
    ioctl(fd, SIOCGIFADDR, &ifr);
    /*closing fd*/
    close(fd);
     
    /*Extract IP Address*/
    strcpy(ip_address,inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));

	return ip_address;
}

void
communicate_prog_1(char *host)
{
	CLIENT *clnt;
	bool_t* result;
	bool_t  *result_1;
	bool_t  *result_2;
	char *leave_1_IP;
	int leave_1_Port;
	bool_t  *result_3;
	char *subscribe_1_IP;
	int subscribe_1_Port;
	char *subscribe_1_Article;
	bool_t  *result_4;
	char *unsubscribe_1_IP;
	int unsubscribe_1_Port;
	char *unsubscribe_1_Article;
	bool_t  *result_5;
	char *publish_1_Article;
	char *publish_1_IP;
	int publish_1_Port;
	bool_t  *result_6;

#ifndef	DEBUG
	clnt = clnt_create (host, COMMUNICATE_PROG, COMMUNICATE_VERSION, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	clients.clear();
	string line;
	ifstream myfile("test.txt");
	if (myfile.is_open())
	{
		while (getline (myfile,line))
		{	
			if (line == "") continue;

			stringstream ss(line);
			string cmd;
			ss >> cmd;
			if (cmd[0] == '#') continue;
			
			if (cmd == "create") {
				cout << "create" << endl;
				ClientAddress addr;
				strcpy(addr.ip, getIP());
				addr.port = 6000 + clients.size();
				clients.push_back(addr);
			} else if (cmd == "join") {
				int id;
				ss >> id;
				cout << "Client " << id << "called join()" << endl;

				result_1 = join_1(clients[id].ip, clients[id].port, clnt);
				if (result_1 == (bool_t *) NULL) {
					clnt_perror (clnt, "call join() failed");
				}
			} else if (cmd == "leave") {
				int id;
				ss >> id;
				cout << "Client " << id << "called leave()" << endl;

				result_1 = leave_1(clients[id].ip, clients[id].port, clnt);
				if (result_1 == (bool_t *) NULL) {
					clnt_perror (clnt, "call leave() failed");
				}
			} else if (cmd == "subscribe") {
				int id;
				ss >> id;
				cout << "Client " << id << "called subscribe()" << endl;

				string s;
				char article[MAXSTRING];
				ss >> article;
				strcpy(article, s.c_str());

				result_1 = subscribe_1(clients[id].ip, clients[id].port, article, clnt);
				if (result_1 == (bool_t *) NULL) {
					clnt_perror (clnt, "call subscribe() failed");
				}
			} else if (cmd == "unsubscribe") {
				int id;
				ss >> id;
				cout << "Client " << id << "called unsubscribe()" << endl;

				string s;
				char article[MAXSTRING];
				ss >> article;
				strcpy(article, s.c_str());

				result_1 = unsubscribe_1(clients[id].ip, clients[id].port, article, clnt);
				if (result_1 == (bool_t *) NULL) {
					clnt_perror (clnt, "call unsubscribe() failed");
				}
			} else if (cmd == "publish") {

			} else {
				cout << "Unknown command" << endl;
			}
		}
		myfile.close();
	}


	
	result_4 = unsubscribe_1(unsubscribe_1_IP, unsubscribe_1_Port, unsubscribe_1_Article, clnt);
	if (result_4 == (bool_t *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	result_5 = publish_1(publish_1_Article, publish_1_IP, publish_1_Port, clnt);
	if (result_5 == (bool_t *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	result_6 = ping_1(clnt);
	if (result_6 == (bool_t *) NULL) {
		clnt_perror (clnt, "call failed");
	}
#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


int
main (int argc, char *argv[])
{
	char *host;

	if (argc < 2) {
		printf ("usage: %s server_host\n", argv[0]);
		exit (1);
	}
	host = argv[1];
	CLIENT *clnt = clnt_create (host, COMMUNICATE_PROG, COMMUNICATE_VERSION, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
	char ip_1[] = "127.0.0.1";
	char ip_2[] = "127.0.0.2";
	char ip_3[] = "127.0.0.3";
	char ip_4[] = "127.0.0.4";
	int port = 5105;
	join_1(ip_1,port,clnt);
	join_1(ip_1,port,clnt);
	join_1(ip_2,port,clnt);
	join_1(ip_3,port,clnt);
	leave_1(ip_4,port,clnt);
	join_1(ip_4,port,clnt);
	leave_1(ip_1,port,clnt);
	communicate_prog_1 (host);
exit (0);
}
