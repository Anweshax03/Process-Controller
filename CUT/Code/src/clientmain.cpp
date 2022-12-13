#include<iostream>
#include<string>
#include<unistd.h>
#include<vector>
#include<map>
#include<algorithm>
#include<iterator>
#include "../include/client.h"

using namespace std;

void printMenu()
{
		cout<<"Select an option from the below menu"<<endl;
		cout<<"2.Stop the running process"<<endl
		    <<"3.Resume the stopped process"<<endl
	            <<"4.Kill the process"<<endl
	            <<"5.Display status of process"<<endl
		    <<"6.Deleting the process from the list of PM"<<endl
		    <<"7.Exit"<<endl;
}


int main()
{
	
	int op,in;
	int pid;
	int j;
	int flag=0;
	vector<int> v1;
	map<int,int> m;
	Client c;
	c.connectToServer();

	cout<<"Select an option from the below menu"<<endl;
	cout<<"Select option 1 first before selecting other options"<<endl;
	cout<<"1.Add the list of processes to PM"<<endl	
	    <<"2.Stop the running process"<<endl
	    <<"3.Resume the stopped process"<<endl
	    <<"4.Kill the process"<<endl
	    <<"5.Display status of process"<<endl
	    <<"6.Deleting the process from the list of PM"<<endl
	    <<"7.Exit"<<endl;
	
	while(1)
	{
		cin>>op;
		cin.ignore();
		switch(op)
		{
			case 1:
				if(flag==0)
				{
					flag=1;
					cout<<"User can enter upto 4 programs only"<<endl;
					cout<<"How many processes user wants to give as input"<<endl;
			        	cin>>j;
					c.sendNP(j);
					for(int k=0;k<j;k++)
					{
				       	    cout<<"Enter process pid"<<endl;
				       	    cin>>pid;
					    vector<int>::iterator it;
				             it = find (v1.begin(), v1.end(), pid);
					    if(it==v1.end())
					    {
						    v1.push_back(pid);
						    m.insert(make_pair(k+1,pid));
						    c.sendPid(pid);
					    }
					    else
					    {
						    cout<<"Pid already inserted"<<endl;
						    cout<<"Enter other pid"<<endl;
						    k--;
					    }
				        }
				}
				else
				{
					cout<<"User has already selected this option and cannot select again"<<endl;
				}
				sleep(4);
				system("clear");
				break;
			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
				if(flag==1)
				{
					cout<<"Available processes: "<<endl;
					for(auto it=m.begin();it!=m.end();it++)
					{
						cout<<it->first<<" "<<it->second<<endl;
					}
					cout<<"Enter process number"<<endl;
			        	cin>>in;
					cin.ignore();
					c.sendOption(op,in);
					c.receiveData();
					if(op==6||op==4)
						m.erase(in);
				}
				else
				{
					cout<<"User cannot select other option without selecting option1"<<endl
						<<"Select  option 1 to add proesses\n"<<endl;
				}
				sleep(4);
				system("clear");

				break;
			case 7:
				cout<<"Exiting the user"<<endl;
				c.closeConnection();
				exit(0);

			default:
				cout<<"Invalid option select valid option"<<endl<<endl;
				break;
		}
		printMenu();
	}
		
	return 0;
}

