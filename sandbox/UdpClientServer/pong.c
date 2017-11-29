#include <stdio.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <string.h>

#define BUFSIZE 24
int main(int argc, char** argv)
{
	unsigned short port = 3001;
	
	int s = socket(AF_INET, SOCK_DGRAM,0);
	
	struct sockaddr_in sock_address;
	struct sockaddr_in remote_address;
	
	inet_aton("10.1.0.3", &sock_address.sin_addr);
	sock_address.sin_port   = htons(port);
	sock_address.sin_family = AF_INET;
	
	//remote
	inet_aton("10.1.0.10", &remote_address.sin_addr);
	remote_address.sin_port   = htons(3000);
	remote_address.sin_family = AF_INET;
	
	int serverlen = sizeof(sock_address);
	int bind_result = bind(s, (struct sockaddr*) &sock_address, sizeof(sock_address));
	char buf[BUFSIZE];
	printf("wait incoming packets \n");
	while(true)
	{
		//printf("wait incomint packets \n");
		
		//int nb = recv(s, buf, BUFSIZE, 0);
		
		//get also source ip
		//recv from 3001
		int nb = 0;
		do
		{
			nb = recvfrom(s, buf, BUFSIZE, MSG_DONTWAIT, 
			(struct sockaddr*) &sock_address, &serverlen);
		}
		while(nb <= 0);
		
		//printf("ip = %s, port = %d \n",inet_ntoa(sock_address.sin_addr), 
		//ntohs(sock_address.sin_port));
		
		//send to 3000
		sendto(s, buf, strlen(buf), 0, 
		(struct sockaddr*)&remote_address, sizeof(remote_address));
		
		//printf("num_bytes = %d \n",nb);

	}


	return 0;
}
