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
	
	inet_aton("192.168.202.129", &sock_address.sin_addr);
	sock_address.sin_port   = htons(port);
	sock_address.sin_family = AF_INET;
	int serverlen = sizeof(sock_address);
	int bind_result = bind(s, (struct sockaddr*) &sock_address, sizeof(sock_address));
	char buf[BUFSIZE];
	while(true)
	{
		printf("wait incomint packets \n");
		
		//int nb = recv(s, buf, BUFSIZE, 0);
		
		//get also source ip
		int nb = recvfrom(s, buf, BUFSIZE, 0, 
		(struct sockaddr*) &sock_address, &serverlen);
		printf("ip = %s, port = %d \n",inet_ntoa(sock_address.sin_addr), 
		ntohs(sock_address.sin_port));
		
		printf("num_bytes = %d \n",nb);

	}


	return 0;
}
