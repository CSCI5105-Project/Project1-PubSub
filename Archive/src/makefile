OBJS = super_server super_server.o stringTokenizer.o server

all : super_server
	
super_server : super_server.o stringTokenizer.o
	g++ -g -o super_server super_server.o stringTokenizer.o -lpthread
	g++ -o server PubSub_svc.cpp PubSub_server.cpp PubSub_xdr.cpp client.h client.cpp stringTokenizer.h stringTokenizer.cpp -lpthread
	g++ -o client PubSub_clnt.cpp PubSub_client.cpp PubSub_xdr.cpp client.h client.cpp stringTokenizer.h stringTokenizer.cpp -lpthread

stringTokenizer.o : stringTokenizer.cpp
	g++ -g -c -o stringTokenizer.o stringTokenizer.cpp

super_server.o : super_server.cpp
	g++ -g -c -o super_server.o super_server.cpp

clean : 
	rm -rf $(OBJS)

new : 
	$(MAKE) clean
	$(MAKE)
