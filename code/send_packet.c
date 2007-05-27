/*
 * send_packet.c - send broadcast random or all '1' packet with delay time.
 *
 * Thanks to Gardon Zhou/SerComm.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/utsname.h>
#include <syslog.h>
#include <stdio.h>
#include <netdb.h>
#include <ctype.h>
#include <pwd.h>

int setup_syslog_socket(unsigned int interface, unsigned short port)
{
	struct sockaddr_in sa_recv;
	int sockfd=-1;
	
	if ((sockfd=socket(AF_INET,SOCK_RAW,IPPROTO_UDP))==-1)	
		return -1;
	
	bzero((char *) &sa_recv, sizeof(sa_recv));
	sa_recv.sin_family=AF_INET;
	sa_recv.sin_addr.s_addr=htonl(interface);
	sa_recv.sin_port=htons(port);
	
	
	if(bind(sockfd,(struct sockaddr *) &sa_recv,sizeof(sa_recv)) == -1) {
		perror("bind");
		return -1;
	}
	return sockfd;
}


int syslog_process_flow(int sockfd, char * syslog_server,unsigned short port,char *buff)
{
	int retval,ret;
	struct sockaddr_in syslog_to;
	const int on=1;
	/*syslog_to.sin_len = sizeof(struct sockaddr_in);*/
	syslog_to.sin_family=AF_INET;
	/*memcpy(&syslog_to.sin_addr.s_addr,syslog_server,4);*/
	syslog_to.sin_addr.s_addr=inet_addr(syslog_server);
	/*syslog_to.sin_addr.s_addr=syslog_server;*/
	syslog_to.sin_port=htons(port);
	
	/*send the syslog*/
	ret = setsockopt( sockfd, SOL_SOCKET, SO_BROADCAST , &on, sizeof(on) );
	if (ret < 0) {
	printf("in the syslog_process_flow, the ret = %d\n",ret);
	}
	retval = sendto(sockfd,buff,strlen(buff),0,(struct sockaddr *)&syslog_to,sizeof(struct sockaddr_in)); 
	return retval;
	
}

int main(int argc, char **argv)
{
	int sockfd=-1;
	int c;
	char *buff = NULL;
	int rand = 0;
	char syslog_server[256];
	int syslog_port;
	int delay = 1;
	int  ret;
	int fd;
	for (;;)
	{
		c = getopt( argc, argv, "d:r:");
		if (c == EOF) break;
		switch (c) 
		{
			case 'd':
				delay = atoi(optarg);
				break;
			case 'r':
				rand = 1;
				break;

			default:
				exit(1);
		}
	}
	
	if(0 == syslog_port)
		syslog_port = 5140;
	
	while((sockfd=setup_syslog_socket(INADDR_ANY,0))<0)
	{
			printf("sockfd error\n");
	}

	// Set *buff
	buff = malloc(1024);
	printf("rand=%d, delay=%ds\n", rand, delay);
	if (rand == 0)
	    memset(buff, 0x11, 1024);

	// Send packet
	while(1){
	    if (rand != 0) {
		fd = open ("/dev/urandom", O_RDONLY | O_NONBLOCK);
		ret = read(fd, buff, 1024);
		close(fd);
	    }
	    ret = syslog_process_flow(sockfd, syslog_server,syslog_port, buff);	
	    printf("ret=%d\n",ret);
	    if( ret < 0)
		printf("sendto error, errno:%d\n", errno);
	    if (delay != 0)
		sleep(delay);
	}
	close(sockfd);
	return 0;

}
