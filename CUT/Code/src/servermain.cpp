#include<iostream>
#include<unistd.h>
#include "../include/server.h"

using namespace std;

int main()
{
	Server s;
	s.startServer(5679);
	s.acceptClient();
	s.waitForThread();
	return 0;
}
