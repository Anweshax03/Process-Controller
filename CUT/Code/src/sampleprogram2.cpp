#include<iostream>
#include<unistd.h>

using namespace std;
int main()
{
	cout<<"hello i am process2"<<endl;
	cout<<"my pid is "<<getpid()<<endl;
	for(;;);	
	return 0;
}
