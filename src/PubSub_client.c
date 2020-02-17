/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "PubSub.h"


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
	communicate_prog_1 (host);
exit (0);
}
