CC = gcc
CCFLAGS = -Wall -Wextra -Werror

all: w12_server w12_client

w12_server: w12_server.o
	$(CC) $< -o $@

w12_client: w12_client.o
	$(CC) $< -o $@

w12_server.o: server.c
	$(CC) $(CCFLAGS) -c $< -o $@

w12_client.o: client.c
	$(CC) $(CCFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f w12_server w12_client w12_server.o w12_client.o
