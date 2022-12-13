#ifndef CLIENT_H
#define CLIENT_H

#include<iostream>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h> // multi threading
#include <errno.h>
#include<vector>
#include<fstream>
#include<cstring>
#define PORT 5679
#define IP "127.0.0.1"
using namespace std;
//int v[4];

class Client
{
	private:
		int sockfd;
		struct sockaddr_in serverAddr;
		fstream op1;

	public:
		Client();
		void connectToServer();
		void sendPid(int pid);
		void sendOption(int op,int in);
		void sendNP(int n);
		void closeConnection();
		void receiveData();
};

#endif
