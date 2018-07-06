#include <stdio.h>
#include <pthread.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#define SRVPORT 1234
#define BUFSIZE 1024
int main()
{
	int s,s_cl, len;
	char buf[BUFSIZE];
	struct sockaddr_in sin, sin_cl;
	s = socket(AF_INET, SOCK_STREAM, 0);
	memset((char *)&sin, '\0', sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = SRVPORT;
	bind(s, (struct sockaddr*)&sin, sizeof(sin));
	listen(s, 10);
	while(1)
	{
		s_cl = accept(s, (struct sockaddr*)&sin_cl, &len);
		send(s_cl, "Hello on my server", 64,0);
		printf("%s\n", inet_ntoa(sin_cl.sin_addr));
		shutdown(s_cl,0);
		close(s_cl);
	}
	close(s);
}