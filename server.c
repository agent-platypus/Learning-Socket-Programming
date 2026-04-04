#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>


int main(int argc, char* argv[]) {

    struct sockaddr_storage client_addr;
    socklen_t addr_sz;
    struct addrinfo hints, *res;
    int status;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    status = getaddrinfo(NULL, "6969", &hints, &res);

    if (status < 0) {
        fprintf(stderr, "Get Addr call failed: %s\n", gai_strerror(status));
        return 1;
    }

    int server_fd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

    if (server_fd < 0) {
        perror("Server file descriptor allocation failed\n");
        return 2;
    }
    
    status = bind(server_fd, res->ai_addr, res->ai_addrlen);

    if(status < 0) {
        perror("Binding socket file descriptor failed\n");
        return 3;
    }

    //// printing server IP ////
    // void* addr;
    // struct sockaddr_in *ip;
    // char ipstr[INET_ADDRSTRLEN];
    // ip = (struct sockaddr_in*) res->ai_addr;
    // addr = &(ip->sin_addr);
    // inet_ntop(res->ai_family, addr, ipstr, sizeof(ipstr));
    // printf("IP address of server = %s\n", ipstr);
    //// printing server IP////// 
    status = listen(server_fd, 10);
    if (status < 0) {
        perror("Listen failed\n");
        return 4;
    }
    
    addr_sz = sizeof(client_addr);
    
   
    int new_fd = accept(server_fd, (struct sockaddr*)&client_addr, &addr_sz);
    
    void* addr;
    struct sockaddr_in *client_ip;
    char clientipstr[INET_ADDRSTRLEN];

    if(new_fd > 0) {
        client_ip = (struct sockaddr_in*) &client_addr;
        addr = &(client_ip->sin_addr);
        inet_ntop(client_addr.ss_family, addr, clientipstr, sizeof(clientipstr));
        printf("Connection established!");
        printf("Client IP = %s\n", clientipstr);
    }



    while(1) {
        printf("Enter a message to send to the client = ");
        char message[100];
        int msglen;
        int bytes_sent;
        if(fgets(message, sizeof(message), stdin)) {
            msglen = strlen(message);
            bytes_sent = send(new_fd, message, msglen + 1, 0);

            if(bytes_sent < 0) {
                perror("Error sending message\n");
            }
        }
        
        printf("Number of Bytes transmitted = %d ", bytes_sent);
        printf("Num bytes of actual message = %d\n", msglen);
        
        printf("Message sent from client = \n");
        char rxbuf[100];
        int bytesRX = recv(new_fd, rxbuf, sizeof(rxbuf), 0);

        if(bytesRX < 0) {
            perror("Sever reception error\n");
        }

        printf("Server message recevied from client = \n");
        printf("%s\n", rxbuf);
    }

    close(server_fd);
    return 0;

}