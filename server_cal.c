#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

typedef struct _Packet {
    int len;
    char msg[1024];
    int result;
}Packet;

void calculation(Packet* packet);
void error_handling(char* msg);

int main(int argc, char** argv) {
    if (argc != 2) {
        error_handling("use port!");
    }
    int port = atoi(argv[1]);
    int server_fd, client_fd;
    struct sockaddr_in serv_addr, client_addr;


    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        error_handling("SOCKET()");
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(server_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) {
        error_handling("BIND()");
    }

    if (listen(server_fd, 5) == -1) {
        error_handling("LISTEN()");
    }

    while (1) {
        Packet packet;
        memset(&packet, 0, sizeof(Packet));
        socklen_t client_len = sizeof(client_addr);
        client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);
        int read_byte = recv(client_fd, &packet, sizeof(Packet), 0);
        printf("Request : %c\n", packet.msg[0]);


        calculation(&packet);
        send(client_fd, &packet, sizeof(packet), 0);
        printf("Response : %c result: %d\n", packet.msg[2], packet.result);
    }
    return 0;
}

void calculation(Packet* packet) {
    int c1 = (int)packet->msg[0]-48;
    int c2 = (int)packet->msg[2]-48;
    char op=packet->msg[1];
    switch (op) {
        case '+':
            packet->result = c1 + c2;
            break;
        case '-':
            packet->result = c1 - c2;
            break;
        case '*':
            packet->result = c1 * c2;
            break;
        case '/':
            packet->result = c1 / c2;
            break;
    }
    return;
}

void error_handling(char* msg) {
    printf("%s\n", msg);
    exit(1);
}
