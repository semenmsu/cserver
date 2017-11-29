#include <stdio.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <string.h>

int main(int argc, char** argv)
{
	/*
	if (argc != 2)
	{
		return -1;
	}*/
	
	unsigned short port = 3000;
	unsigned short remote_port = 3000;
	
	int s = socket(AF_INET, SOCK_DGRAM, 0);
	int s_remote = socket(AF_INET, SOCK_DGRAM, 0);
	/*
	*/
	struct sockaddr_in sock_address;
	struct sockaddr_in remote_address;
	
	//sock
	inet_aton("10.1.0.3", &sock_address.sin_addr);
	sock_address.sin_port   = htons(port);
	sock_address.sin_family = AF_INET;
	
	//remote
	inet_aton("10.1.0.1", &remote_address.sin_addr);
	remote_address.sin_port   = htons(remote_port);
	remote_address.sin_family = AF_INET;
	
	int bind_result = bind(s, (struct sockaddr*)&sock_address, sizeof(sock_address));
	//bind_result = bind(s_remote, (struct sockaddr*)&sock_address, sizeof(sock_address));
	
	char* buff = "send\n";
	while(true)
	{
		printf("%s \n",buff);
		printf("size = %d \n",(int)strlen(buff));
		sendto(s, buff, strlen(buff), 0, 
		(struct sockaddr*)&remote_address, sizeof(remote_address));
		usleep(1000000);
	}
	
	return 0;
	
	
	
}
