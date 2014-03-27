#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h>

using namespace std;

int readline (int s, string &str, int buffsize);


int main () {

	int sock_client = socket(AF_INET, SOCK_STREAM, 0);
	if(sock_client < 0)
	{
	    cout << "Error: Could not create socket!" << endl;
	    return 1;
	}
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	struct hostent* host = gethostbyname("localhost");
	addr.sin_family = host->h_addrtype;
	memcpy(&(addr.sin_addr.s_addr), host->h_addr, host->h_length);
	addr.sin_port = htons(22522);
	if( connect(sock_client, (sockaddr*)&addr, sizeof(addr)) != -1) {
		while ( 1 ) {
			cout << "Enter Command: " << flush;
			string cmd_in;
			getline(cin, cmd_in);	
			cmd_in += "\n";

			send(sock_client, cmd_in.c_str(), cmd_in.size(), 0);

			string data;
			if(readline(sock_client, data, 4096) == -1) break;
			cout << data << endl; 
		}

	} else {
		cout << "not even shit." << endl;
	}
}

int readline (int s, string &str, int buffsize)
{
    str = "";
	int ret = 0;
	char nc = 0;
	for(int i = 0; i < buffsize; i++)
	{
	    if(recv(s, &nc, 1, 0) != 1) return -1;
	    if(nc == '\n') return i;
	    str += nc;
	}
	return str.size();
}
