#ifndef SERVER_H
#define SERVER_H

#include<iostream>
#include<string>
#include<sys/socket.h>
#include<netinet/in.h>
#include<signal.h>
#include<cstring>
#include<errno.h>
#include<fstream>
#include<unistd.h>
#include<vector>
#include<pthread.h>
#include<set>

using namespace std;
#define SERVER_PORT 5679;


class Server
{
	private:
		int sockfd;
		int clientfd;
		int n;
		struct sockaddr_in socketAddr;
		struct sockaddr_in clientAddr;
		ofstream op1;
		pthread_t t;
	public:
		Server();
		Server(int,int);
		int getClientfd();
		int getSockfd();
		void startServer(int port);
		void acceptClient();
		void receiveData();
		void receiveNP();
		void receivePid();
		void sendMsg();
		static void* clienthandler(void* );
		void waitForThread();

};

#endif
		
