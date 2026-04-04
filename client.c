#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>


int main(int argc, char* argv[]) {
    struct addrinfo hints, *res;
    int status;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    status = getaddrinfo("0.0.0.0", "6969", &hints, &res);

    if (status < 0) {
        fprintf(stderr, "Get Addr call failed: %s\n", gai_strerror(status));
        return 1;
    }

    int client_fd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

    if (client_fd < 0) {
        perror("Client file descriptor allocation failed\n");
        return 2;
    }
    
    status = connect(client_fd, res->ai_addr, res->ai_addrlen);

    if (status < 0) {
        perror("Client connect call failed\n");
        return 3;
    }   

    char rxbuf[100];
    char txbuf[100];
    int msglen;
    int numBytes;
    while(1) {
        
        int numBytesRx = recv(client_fd, rxbuf, sizeof(rxbuf), 0);

        if (numBytesRx < 0) {
            perror("Reception error\n");
        }
        printf("Received message from server = %s\n", rxbuf);
        
        printf("Enter message to send to server =\n");
        if(fgets(txbuf, sizeof(txbuf), stdin)) {
            msglen = strlen(txbuf);
            numBytes = send(client_fd, txbuf, msglen + 1, 0);

            if (numBytes < 0) {
                perror("Error sending message\n");
            }
        }
    
    }

    close(client_fd);
    return 0;
}