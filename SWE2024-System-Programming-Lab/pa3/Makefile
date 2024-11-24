CC = gcc
CCFLAGS = # -Wall -Wextra -Werror
LDFLAGS = -pthread

all: pa3_server pa3_client

pa3_server: pa3_server.o
	$(CC) $< -o $@ $(LDFLAGS)

pa3_client: pa3_client.o
	$(CC) $< -o $@

pa3_server.o: server.c
	$(CC) $(CCFLAGS) -c $< -o $@

pa3_client.o: client.c
	$(CC) $(CCFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f pa3_server pa3_client pa3_server.o pa3_client.o