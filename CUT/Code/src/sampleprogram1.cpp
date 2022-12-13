#include<iostream>
#include<string>
#include<unistd.h>
using namespace std;
int main()
{
		cout<<"hello"<<endl;
		cout<<"my pid is "<<getpid()<<endl;
		cout<<"I am an infinite loop"<<endl;
		while(1);
	return 0;
}
