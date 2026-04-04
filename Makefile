CC = gcc
CFlags = -Wall 

all: server client

server: server.o
	$(CC) server.c -o server $(CFlags)

server.o: server.c 
	$(CC) $(CFlags) -c server.c

client: client.o
	$(CC) client.c -o client $(CFlags)

client.o: client.c
	$(CC) $(CFlags) -c client.c

clean: 
	rm -f server client *.o