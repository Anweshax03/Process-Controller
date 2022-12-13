#include<iostream>
#include<unistd.h>
#include<string>

using namespace std;

int main()
{
	cout<<"hello"<<endl;
	cout<<"my pid is "<<getpid()<<endl;
	sleep(10*60);
	return 0;
}
