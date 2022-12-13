#include<iostream>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h> 
#include <errno.h>
#include<fstream>
#include<vector>
#include<cstring>
#include "../include/client.h"
#define PORT 5679
#define IP "127.0.0.1"
using namespace std;

Client::Client()
{
}
//connecting to server

void Client::connectToServer()
{
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd==-1)
	{
		perror("socket:");
		exit(-1);
	}
	memset(&serverAddr,0,sizeof(serverAddr));
	serverAddr.sin_family=AF_INET;
	serverAddr.sin_port=htons(PORT);
	serverAddr.sin_addr.s_addr=inet_addr(IP);
	int l=sizeof(struct sockaddr_in);
	int rc = connect(sockfd, (struct sockaddr *)&serverAddr, l);
	if(rc < 0)

  	{		

    		perror("client - connect() error");

    		close(sockfd);

    		exit(-1);

  	}
	else
	{
		op1.open("logfile1.txt",ios::app);
		op1<<"info:client connecting to the server"<<endl;
	}
}

//sending number of process to server
void Client::sendNP(int np1)
{
	int n=np1;
	char buf1[100];
	memcpy(buf1,&n,sizeof(int));
	int r=send(sockfd,buf1,sizeof(int),0);
	if(r<0)
	{
		cout<<"error in send"<<endl;
	}
}

//sending pids to server
void Client::sendPid(int pid)
{
	char buf[100];
	memcpy(buf,&pid,sizeof(pid));
	int s=send(sockfd,buf,sizeof(int),0);
	if(s<0)
	{
		cout<<"error in send"<<endl;
	}
}


//sending user selected option and process number to server
void Client::sendOption(int op,int pn)
{
	char buf1[100],buf[100];
	memcpy(buf1,&op,sizeof(int));
	int s=send(sockfd,buf1,sizeof(int),0);
	if(s<0)
	{
		cout<<"error in send"<<endl;
	}
	sleep(1);
	memcpy(buf,&pn,sizeof(int));
	int p=send(sockfd,buf,sizeof(int),0);
	if(p<0)
	{
		cout<<"error in send"<<endl;
	}

}

//receiving message from server
void Client::receiveData()
{
	char b[100];
	int r=recv(sockfd,b,sizeof(b),0);
	b[r]='\0';
	cout<<b<<endl<<endl;
	op1<<"Client received data from client"<<endl;
}

//closing client connection
void Client::closeConnection()
{
	cout<<"Disconnecting from the server"<<endl;
	op1<<"Client closed its connection"<<endl;
	close(sockfd);
}
