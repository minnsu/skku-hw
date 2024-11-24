#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#define MAXLINE 91

int main (int argc, char *argv[]) {
    ssize_t num_bytes;
    int connected_fd;
    struct hostent *host_entry;
    struct sockaddr_in socket_address;
    char buffer[MAXLINE];

    if (argc < 3) {
        printf("Received %d arguments. Please enter host address and port number!\n", argc - 1);
        exit(1);
    }

    char* host = argv[1];
    uint16_t port = (uint16_t)strtol(argv[2], NULL, 10);

    if ((connected_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        printf("socket() failed.\n"); 
        exit(2);
    }

    if ((host_entry = gethostbyname(host)) == NULL) {
        printf("invalid hostname %s\n", host); 
        exit(3);
    }

    memset((char *)&socket_address, 0, sizeof(socket_address));
    socket_address.sin_family = AF_INET;
    memcpy((char *)&socket_address.sin_addr.s_addr, (char *)host_entry->h_addr, (size_t) host_entry->h_length);
    socket_address.sin_port = htons(port);

    if (connect(connected_fd,(struct sockaddr *)&socket_address,sizeof(socket_address)) < 0) {
        printf("connect() failed.\n");
        exit(4);
    }

    char user[11];
    char new_buf[MAXLINE];
    printf("Insert your name : ");
    scanf("%s", user);
    write(connected_fd, user, (size_t) 11);
    read(connected_fd, buffer, MAXLINE);
    memset(buffer, 0, MAXLINE);

    fd_set read_set;
    FD_ZERO(&read_set);
    FD_SET(connected_fd, &read_set);
    FD_SET(STDIN_FILENO, &read_set);
    int fd_num, fd_max = connected_fd;

    while((fd_num = select(fd_max + 1, &read_set, NULL, NULL, NULL)) > 0) {
        for(int i = 0; i < fd_max + 1; i++) {
            if(FD_ISSET(i, &read_set)) {
                if(i == connected_fd) {
                    num_bytes = read(connected_fd, buffer, MAXLINE);
                    int i;
                    for(i = 0; i < 11; i++){
                        if(buffer[i] == ':')
                            break;
                        if(buffer[i] != user[i]){
                            write(STDOUT_FILENO, buffer, (size_t) num_bytes);
                            break;
                        }
                    }
                } else if(i == STDIN_FILENO) {
                    num_bytes = read(STDIN_FILENO, buffer, MAXLINE);
                    sprintf(new_buf, "%s:%s", user, buffer); // "<username> buffer"
                    write(connected_fd, new_buf, (size_t) num_bytes + strlen(user) + 1);
                    if(!strncmp(buffer, "quit", 4)) {
                        goto end;
                    }
                }
                FD_CLR(i, &read_set);
            }
        }
        FD_SET(STDIN_FILENO, &read_set);
        FD_SET(connected_fd, &read_set);
    }
    end:
    close(connected_fd);

    return 0;
}
