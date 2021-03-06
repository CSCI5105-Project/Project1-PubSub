/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include <memory.h> /* for memset */
#include "PubSub.h"

/* Default timeout can be changed using clnt_control() */
static struct timeval TIMEOUT = { 25, 0 };

bool_t *
join_1(char *IP, int Port,  CLIENT *clnt)
{
	join_1_argument arg;
	static bool_t clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	arg.IP = IP;
	arg.Port = Port;
	if (clnt_call (clnt, Join, (xdrproc_t) xdr_join_1_argument, (caddr_t) &arg,
		(xdrproc_t) xdr_bool, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

bool_t *
leave_1(char *IP, int Port,  CLIENT *clnt)
{
	leave_1_argument arg;
	static bool_t clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	arg.IP = IP;
	arg.Port = Port;
	if (clnt_call (clnt, Leave, (xdrproc_t) xdr_leave_1_argument, (caddr_t) &arg,
		(xdrproc_t) xdr_bool, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

bool_t *
subscribe_1(char *IP, int Port, char *Article,  CLIENT *clnt)
{
	subscribe_1_argument arg;
	static bool_t clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	arg.IP = IP;
	arg.Port = Port;
	arg.Article = Article;
	if (clnt_call (clnt, Subscribe, (xdrproc_t) xdr_subscribe_1_argument, (caddr_t) &arg,
		(xdrproc_t) xdr_bool, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

bool_t *
unsubscribe_1(char *IP, int Port, char *Article,  CLIENT *clnt)
{
	unsubscribe_1_argument arg;
	static bool_t clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	arg.IP = IP;
	arg.Port = Port;
	arg.Article = Article;
	if (clnt_call (clnt, Unsubscribe, (xdrproc_t) xdr_unsubscribe_1_argument, (caddr_t) &arg,
		(xdrproc_t) xdr_bool, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

bool_t *
publish_1(char *Article, char *IP, int Port,  CLIENT *clnt)
{
	publish_1_argument arg;
	static bool_t clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	arg.Article = Article;
	arg.IP = IP;
	arg.Port = Port;
	if (clnt_call (clnt, Publish, (xdrproc_t) xdr_publish_1_argument, (caddr_t) &arg,
		(xdrproc_t) xdr_bool, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

bool_t *
ping_1(CLIENT *clnt)
{
	static bool_t clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	 if (clnt_call (clnt, Ping, (xdrproc_t) xdr_void, (caddr_t) NULL,
		(xdrproc_t) xdr_bool, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}
