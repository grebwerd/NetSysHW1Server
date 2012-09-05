/*
 * upd_server.c
 *
 *  Created on: Sep 4, 2012
 *      Author: grebwerd
 */


#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>

#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include <netdb.h>
#include <unistd.h>

#define MAXBUFSIZE 100

int main(int argc, char *argv[])
{
   int sock, length, fromlen, n;
   struct sockaddr_in server;
   struct sockaddr_in from;
   char buf[MAXBUFSIZE];

   //Verify that the user inputs the correct number of arguments
   if (argc < 2) {
      printf("USAGE: <port> \n");
      exit(1);
   }

   //Create a new IPv4 udp socket
   sock=socket(AF_INET, SOCK_DGRAM, 0);

   if (sock < 0) {
	printf("unable to create a socket");
   }

   length = sizeof(server);
   //fill the first length number of bytes in server struct with zeros
   bzero(&server,length);

   //make sure that server uses IPv4
   server.sin_family=AF_INET;

   //make sure that the socket's IP address is the local host and it is IPv4
   server.sin_addr.s_addr=INADDR_ANY;

   //get the port number as a string and convert to an integer and
  //then make sure that the host and the network both send bytes using the same endiness.
  server.sin_port=htons(atoi(argv[1]));


   if (bind(sock,(struct sockaddr *)&server,length)<0)  {
      printf("unable to bind socket to local ip address\n");
    }
   fromlen = sizeof(struct sockaddr_in);
   while (1) {
	bzero(buf, sizeof(buf));
       n = recvfrom(sock,buf,MAXBUFSIZE,0,(struct sockaddr *)&from,&fromlen);
       if (n < 0) {
	  printf("unable to recvfrom socket");
	}
       printf("Received a datagram of size %d: \n", n);

       printf("Received value: %s\n", buf);
       char msg[] = "orange";
       n = sendto(sock,msg,sizeof(msg),
                  0,(struct sockaddr *)&from,fromlen);
       if (n  < 0) {
		printf("unable to send message using sendto\n");
	}
   }
 }
