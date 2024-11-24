#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include <fcntl.h>
#define MAXLINE 80

int main (int argc, char *argv[]) {
	struct hostent* host_entry; // contains information related to the host like IP address
	struct sockaddr_in socket_address;
	char buffer[MAXLINE], buffer_data[MAXLINE];
	int connecting_fd;

	if (argc < 3){
		printf("Received %d arguments. Please enter host address and port number!\n", argc - 1);
		exit(1);
	}

	char *host = argv[1]; // contains hostname (e.g. "www.skku.edu", "localhost", etc.) 
	uint32_t port = (uint32_t)strtol(argv[2], NULL, 10); // contains port number 

	/* Create socket */
	if((connecting_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0){
		printf("socket() failed.\n");
		exit(2);
	}
	/* Get host information */
	if((host_entry = gethostbyname(host)) == NULL) {
		printf("invalid hostname %s\n", host);
		exit(3);
	}
	/* Connect to host */
	memset((char *)&socket_address, 0, sizeof(socket_address));
	socket_address.sin_family = AF_INET;
	memcpy((char *)&socket_address.sin_addr.s_addr, (char *)host_entry->h_addr_list[0], host_entry->h_length);
	socket_address.sin_port = htons(port);
	if(connect(connecting_fd, (struct sockaddr *)&socket_address, sizeof(socket_address)) < 0){
		printf("connect() failed.\n");
		exit(4);
	}

	int fd;
	size_t fsize = 0;
	while (1) {
		/* Send filename & data */
		int num_bytes = read(STDIN_FILENO, buffer, MAXLINE);
		buffer[strlen(buffer) - 1] = 0;
		if(!strcmp(buffer, "quit")){
			write(connecting_fd, buffer, num_bytes);
			break;
		}

		if((fd = open(buffer, O_RDONLY)) < 0){
			printf("open() failed.\n");
			continue;
		}
		write(connecting_fd, buffer, MAXLINE);
		memset(buffer, 0, MAXLINE);

		memset(buffer_data, 0, MAXLINE);
		while((num_bytes = read(fd, buffer_data, MAXLINE)) > 0){
			fsize += num_bytes;
			write(connecting_fd, buffer_data, num_bytes);
			memset(buffer_data, 0, MAXLINE);
		}
		write(connecting_fd, "\0", 1);
		close(fd);
		printf("Send %ld bytes to server.\n", fsize);
		fsize = 0;
	}

	close(connecting_fd);

	return 0;
}


