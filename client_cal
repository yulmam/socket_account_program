#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

void error_handling(char* msg);

typedef struct _Packet {
    int len;
    char msg[1024];
    int result;
}Packet;


int main(int argc, char** argv) {

    if (argc != 3) {
        error_handling("use 3 argc");
    }

    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(argv[2]));
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);

    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0) {
        error_handling("SOCKET()");
    }
    int err;
    if (connect(sock_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) {
        error_handling("CONNECT()");
    }

    Packet packet;
    memset(&packet, 0, sizeof(Packet));
    scanf("%s", packet.msg);
    send(sock_fd, &packet, sizeof(Packet), 0);


    memset(&packet, 0, sizeof(Packet));
    int read = recv(sock_fd, &packet, sizeof(Packet), 0);
    printf("Reply : %d\n", packet.result);
    return 0;
}

void error_handling(char* msg) {
    printf("%s\n", msg);
    exit(1);
}
