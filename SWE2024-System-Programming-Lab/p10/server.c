#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <fcntl.h>
#define MAXLINE 80

int main (int argc, char* argv[]) {
	int listening_fd, connecting_fd, connecting_address_length;
	// struct hostent* host_entry;
	struct sockaddr_in socket_address, connecting_address;
	char buffer[MAXLINE], buffer_data[MAXLINE];

	if (argc < 2) {
		printf("Received %d arguments. Please enter port number!\n", argc - 1);
		exit(1);
	}

	uint32_t port = (uint32_t)strtol(argv[1], NULL, 10); // contains port number 

	/* Create listen socket */
	if((listening_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0){
		printf("socket() failed.\n");
		exit(2);
	}
	/* Bind sockaddr (IP, etc.) to listen socket */
	memset((char *)&socket_address, 0, sizeof(socket_address));
	socket_address.sin_family = AF_INET;
	socket_address.sin_addr.s_addr = htonl(INADDR_ANY);
	socket_address.sin_port = htons(port);
	if(bind(listening_fd, (struct sockaddr *)&socket_address, sizeof(socket_address)) < 0){
		printf("bind() failed.\n");
		exit(3);
	}
	/* Listen to listen socket */
	if(listen(listening_fd, 5) < 0){
		printf("listen() failed.\n");
		exit(4);
	}
	/* Accept connection request from clients */
	connecting_address_length = sizeof(connecting_address);
	while((connecting_fd = accept(listening_fd, (struct sockaddr *)&connecting_address, (socklen_t *)&connecting_address_length)) < 0){
		printf("accept() failed.\n");
	}

	int num_bytes = 0;
	size_t fsize = 0;
	int fd;
	while (1) {
		/* Receive filename & data */
		memset(buffer, 0, MAXLINE);
		if((num_bytes = read(connecting_fd, buffer, MAXLINE)) > 0){
			if(!strncmp(buffer, "quit", 4)){
				break;
			}
			sprintf(buffer, "%s_copy", buffer);
			if((fd = open(buffer, O_CREAT | O_WRONLY | O_TRUNC, 438)) < 0){
				printf("open() failed.\n");
				break;
			}
			num_bytes = 0;
		}
		memset(buffer_data, 0, MAXLINE);
		while((num_bytes = read(connecting_fd, buffer_data, 1)) > 0){
			if(buffer_data[0] == '\0')
				break;
			write(fd, buffer_data, 1);
			fsize += num_bytes;
			num_bytes = 0;
			memset(buffer_data, 0, MAXLINE);
		}
		close(fd);
		printf("got %ld bytes from client.\n", fsize);
		fsize = 0;
	}

	close(connecting_fd);
	close(listening_fd);

	return 0;
}


