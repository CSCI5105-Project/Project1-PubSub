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

using namespace std;

void
communicate_prog_1(char *host)
{
	CLIENT *clnt;
	bool_t  *result_1;
	char *join_1_IP;
	int join_1_Port;
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
			} else if (cmd == "join") {
				cout << "join" << endl;
			} else if (cmd == "leave") {
				cout << "leave" << endl;
			} else if (cmd == "subscribe") {
				cout << "subscribe" << endl;
			} else if (cmd == "unsubscribe ") {
				cout << "unsubscribe" << endl;
			} else if (cmd == "publish") {

			} else {
				cout << "Unknown command" << endl;
			}
		}
		myfile.close();
	}

	result_1 = join_1(join_1_IP, join_1_Port, clnt);
	if (result_1 == (bool_t *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	result_2 = leave_1(leave_1_IP, leave_1_Port, clnt);
	if (result_2 == (bool_t *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	result_3 = subscribe_1(subscribe_1_IP, subscribe_1_Port, subscribe_1_Article, clnt);
	if (result_3 == (bool_t *) NULL) {
		clnt_perror (clnt, "call failed");
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
