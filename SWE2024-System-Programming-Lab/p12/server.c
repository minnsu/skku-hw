#include <sys/select.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#define MAXLINE 91

int main (int argc, char *argv[]) {
    ssize_t num_bytes;
    size_t connected_address_length;
    int connected_fd, listening_fd;
    struct sockaddr_in socket_address, connected_address;
    char buffer[MAXLINE];

    if (argc < 2) {
        printf("Received %d arguments. Please enter port number!\n", argc - 1);
        exit(1);
    }

    uint16_t port = (uint16_t)strtoul(argv[1], NULL, 10);

    if ((listening_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        printf("socket() failed.\n");
        exit(2);
    }

    memset((char *)&socket_address, 0, sizeof(socket_address));
    socket_address.sin_family = AF_INET;
    socket_address.sin_addr.s_addr = htonl(INADDR_ANY);
    socket_address.sin_port = htons(port);

    if (bind(listening_fd, (struct sockaddr *)&socket_address, sizeof(socket_address)) < 0) {
        printf("bind() failed.\n");
        exit(3);
    }

    if (listen(listening_fd, 5) < 0) {
        printf("listen() failed.\n");
        exit(4);
    }

    fd_set read_set, copy_set;
    FD_ZERO(&read_set);  /* initialize socket set */
    FD_SET(listening_fd, &read_set);
    int fd_max = listening_fd, fd_num;

    int cli_count = 0;
    char user[11];
    while (1) {
        copy_set = read_set;

        if((fd_num = select(fd_max + 1, &copy_set, NULL, NULL, NULL)) < 0 ) {
            printf("select() failed.\n");
            exit(5);
        }

        if (fd_num == 0) {
            printf("Time out.\n");
            continue;
        }

        for (int fd = 0; fd < fd_max + 1; fd++) {
            memset(buffer, 0, MAXLINE);
            if (FD_ISSET(fd, &copy_set)) {
                if (fd == listening_fd) {
                    connected_address_length = sizeof(connected_address);
                    if ((connected_fd = accept(listening_fd, (struct sockaddr*)&connected_address, (socklen_t*)&connected_address_length)) < 0) {
                        printf ("accept() failed.\n");
                        continue;
                    }

                    FD_SET(connected_fd, &read_set);
                    if (fd_max < connected_fd) fd_max = connected_fd;

                    cli_count++;
                    num_bytes = read(connected_fd, user, 11);
                    sprintf(buffer, "%s joined. %d current users\n", user, cli_count);
                    for(int fd2 = 3; fd2 < fd_max + 1; fd2++){
                        if(fd2 != listening_fd){
                            write(fd2, buffer, MAXLINE);
                        }
                    }
                }
                else {
                    if ((num_bytes = read(fd, buffer, MAXLINE)) > 0) {
                        memset(user, 0, 11);
                        for(int i = 0; i < 11; i++){
                            if(buffer[i] != ':')
                                user[i] = buffer[i];
                            else
                                break;
                        }
                        num_bytes -= strlen(user) + 1;
                        if(!strncmp(&buffer[strlen(user) + 1], "quit", 4)) {
                            goto remove;
                        }
                        printf ("got %lu bytes from user %s.\n", num_bytes, user);
                        for(int fd2 = 3; fd2 < fd_max + 1; fd2++){
                            if(fd2 != listening_fd){
                                write(fd2, buffer, MAXLINE);
                            }
                        }
                    }
                    else {
                        remove:
                        FD_CLR(fd, &read_set);
                        cli_count--;
                        sprintf(buffer, "%s leaved. %d current users.\n", user, cli_count);
                        for(int fd2 = 3; fd2 < fd_max + 1; fd2++){
                            if(FD_ISSET(fd2, &read_set) && fd2 != listening_fd){
                                write(fd2, buffer, MAXLINE);
                            }
                        }
                        // printf("connection terminated.\n");
                        close(fd);
                    }
                }
            }
        }
    }
    return 0;
}


