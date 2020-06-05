#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define SERVER_PORT 12000
#define BUF_SIZE 4096
#define OUTFDESC 1

void fatal(char *message);

int main(int argc, char *argv[])
{
    int sock, fbytes;
    char buf[BUF_SIZE];
    struct hostent *hostptr;
    struct sockaddr_in channel;

    if (argc != 3)
        fatal("wywolanie: client <nazwa serwera> <nazwa pliku>");
    hostptr = gethostbyname(argv[1]);
    if (!hostptr)
        fatal("nie mozna uzyskac adresu IP serwera");

    sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock < 0)
        fatal("nie mozna utworzyc gniazda");
    memset(&channel, 0, sizeof(channel));
    channel.sin_family = AF_INET;
    memcpy(&channel.sin_addr.s_addr, hostptr->h_addr, hostptr->h_length);
    channel.sin_port = htons(SERVER_PORT);

    if (connect (sock, (struct sockaddr *) &channel, sizeof(channel)) < 0)
        fatal ("nie powiodlo sie wywolanie funkcji connect");
    
    write(sock, argv[2], strlen(argv[2]) + 1);

    while ((fbytes = read(sock, buf, BUF_SIZE)) > 0)
        write(OUTFDESC, buf, fbytes);
    putchar('\n');
    
    return 0;
}

void fatal(char *message)
{
    printf("%s\n", message);
    exit(1);
}