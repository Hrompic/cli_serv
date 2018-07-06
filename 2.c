#include <stdio.h>
#include <pthread.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netdb.h>
#define BUFSIZE 1024
#define PORT 111
#define SRVPORT 1234
int main()
{
	struct hostent *hp;
	int s, len;
	char buf[BUFSIZE];
	struct sockaddr_in cli_sin, srv_sin;
	s = socket(AF_INET, SOCK_STREAM, 0);
	memset((char*)&cli_sin, '\0', sizeof(cli_sin) );
	cli_sin.sin_family = AF_INET;
	cli_sin.sin_port = PORT;
	cli_sin.sin_addr.s_addr = INADDR_ANY;
	bind(s, (struct sockaddr*)&cli_sin, sizeof(cli_sin));
	memset((char*)&srv_sin, '\0', sizeof(srv_sin) );
	hp = gethostbyname("localhost");
	memcpy((char*)&srv_sin.sin_addr, hp->h_addr, hp->h_length);
	srv_sin.sin_port = SRVPORT;
	srv_sin.sin_family = AF_INET;
	connect(s, (struct sockaddr *)&srv_sin, sizeof(srv_sin));
	recv(s, buf, BUFSIZE, 0);
	printf(buf);
}
