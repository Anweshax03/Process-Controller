#include<iostream>
#include <stdlib.h>
#include <sys/socket.h>
#include<cstring>
#include<unistd.h>
#include<netinet/in.h>
#include<errno.h>
#include<set>
#include<vector>
#include<map>
#include<iterator>
#include<fstream>
#include<signal.h>
#include <netinet/in.h>
#include "../include/server.h"

using namespace std;
int j=0;
map<int,int> m;


Server::Server()
{

}

Server::Server(int a,int b)
{
	sockfd=a;
	clientfd=b;
}

int Server::getClientfd()
{
	return clientfd;
}

int Server::getSockfd()
{
	return sockfd;
}

//creating file descriptor and binding address for server
void Server::startServer(int port)
{
	if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1)
	{
		perror("server:");
		exit(-1);
	}
	memset(&socketAddr, 0, sizeof(socketAddr));
    	socketAddr.sin_family = AF_INET;
   	socketAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    	socketAddr.sin_port = htons(port);
	int l=sizeof(struct sockaddr_in);
	if(bind(sockfd,(struct sockaddr*)&socketAddr,l)==-1)
	{
		perror("bind");
		exit(-1);
	}
	int z=listen(sockfd,2);
	if(z<0)
	{
		perror("listn");
		exit(-1);
	}
}

//Accepting client connections
void Server::acceptClient()
{
	for(int i=0;i<1;i++)
	{
		socklen_t l=sizeof(clientAddr);
		cout<<"Process Manager accepting the connections"<<endl;
		clientfd=accept(sockfd,(struct sockaddr*)&clientAddr,&l);
		if(clientfd==-1)
		{
			perror("accept");
			break;
		}
		else
		{
			op1.open("logfile.txt");
			op1<<"Server accepted client connection"<<endl;
		}

		cout<<"Process Manager accepted the connection\n"<<endl;
		cout<<"**************************************************************************\n"<<endl;
		pthread_create(&t,NULL,clienthandler,this);
		
	}
}

//Handling the client connection
//
void* Server::clienthandler(void* input)
{
	
	Server *srv=(Server*)input;
	srv->receiveNP();
	srv->receivePid();
	srv->receiveData();
	return 0;
}

void Server::waitForThread()
{
		pthread_join(t,NULL);	
}

//receiving the number of processes from client

void Server::receiveNP()
{
	char b[10];
	int n1;
	int d=recv(clientfd,b,sizeof(b),0);
	if(d<0)
	{
		cout<<"Error in receiving"<<endl;
	}
	memcpy(&n1,b,sizeof(int));
	n=n1;
}

//receiving list of pids from client

void Server::receivePid()
{
	int d,r;
	cout<<"PM received list of pids from client"<<endl;
	char b[10];
	for(int i=0;i<n;i++)
	{
		d=recv(clientfd,b,sizeof(b),0);
		if(d<0)
		{
			cout<<"Error in receiving"<<endl;
		}
		memcpy(&r,b,sizeof(int));
		//v.push_back(r);
		m.insert(make_pair(i+1,r));
	}
}

//sending msg to client
void Server::sendMsg()
{
	char f[]="PM deleted process from its list cannot perform operation";
	send(clientfd,f,strlen(f),0);
}

//receiving option and process number from client
void Server::receiveData()
{
	int d=1;
	char b[100],c[100];
	while(1)
	{
		int pn;
		int op;
		cout<<"Process Manager waiting to receive data from client"<<endl;
		d=recv(clientfd,b,sizeof(b),0);
		if(d==0)
		{
			cout<<"Client disconnected from the server"<<endl;
			op1<<"Info:client disconnected from the server"<<endl;
			close(clientfd);
			for(auto it=m.begin();it!=m.end();it++)
			{
				kill(it->second,SIGKILL);
			}
			cout<<"Process Manager stopped all the running processes and closing its connection"<<endl;
			close(sockfd);
			break;
		}
		cout<<"PM received data"<<endl;
		op1<<"Server has received data from client"<<endl;
		memcpy(&op,b,sizeof(int));
		sleep(1);
		int c1=recv(clientfd,c,sizeof(c),0);
		if(c1<0)
		{
			cout<<"Error in receiving"<<endl;
		}
		
		memcpy(&pn,c,sizeof(int));
		//stopping the process
		if(op==2){
			if(m.find(pn)!=m.end()){
			int g=m[pn];
			kill(g,SIGSTOP);
			char f[]="Process Manager suspended the process";
			op1<<"info:server suspended the process"<<endl;
			send(clientfd,f,strlen(f),0);
			cout<<"PM suspended the process with pid "<<g<<endl;
			}
			else
			{
				sendMsg();
			}
		}
		//Resuming the process
		if(op==3){
			if(m.find(pn)!=m.end()){
			int g=m[pn];
			kill(g,SIGCONT);
			char f[]="Process Manager resumed the suspended process";
			op1<<"info:server resumed the process"<<endl;
			send(clientfd,f,strlen(f),0);
			cout<<"PM resumed the process with pid "<<g<<endl;
			}
			else
			{
				sendMsg();
			}
		}
		//Killing the process
		if(op==4){
			if(m.find(pn)!=m.end()){
			int g=m[pn];
			m.erase(pn);
			kill(g,SIGKILL);
			char f[]="Process Manager killed the process";
			op1<<"info:server killed the process"<<endl;
			send(clientfd,f,strlen(f),0);
			cout<<"PM killed the process with pid "<<g<<endl;
			}
			else
				sendMsg();
		}
		//displaying statistics
		if(op==5){
			if(m.find(pn)!=m.end()){
			int g=m[pn];
			cout<<"**************************************************************************\n"<<endl;	
			string s2;
			s2=to_string(g);
			string s="ps -u -f";
			s.append(" ");
			s.append(s2);
			const char *p1=s.c_str();
			system(p1);
			char f[]="Process Manager displayed the status of process";
			op1<<"info:server displayed the status info"<<endl;

			cout<<"\n**************************************************************************\n"<<endl;
			send(clientfd,f,strlen(f),0);
			}
			else
				sendMsg();
		}
		//deleting pid from PM list
		if(op==6)
		{
			if(m.find(pn)!=m.end()){

			int g=m[pn];
			cout<<"PM deleted the process with pid  "<<g<<endl;
			char f[]="PM deleted user selected process from its list";
			send(clientfd,f,strlen(f),0);
			m.erase(pn);
			}
			else
				sendMsg();
		}
	
	}
}




