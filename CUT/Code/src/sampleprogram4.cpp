#include<iostream>
#include<unistd.h>
using namespace std;
int main()
{
	cout<<"hello"endl;
	cout<<getpid()<<endl;
	cout<<I am going into sleep for 20 min"<<endl;
	sleep(20*60);
	return 0;
}
