#include <sys/types.h>
#include <sys/fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#define SERVER_PORT 12000
#define BUF_SIZE 4096
#define QUEUE_SIZE 16

void fatal(char *message);

int main(void)
{
    int sock, consock, fdesc, fbytes, on = 1;
    char buf[BUF_SIZE];
    struct sockaddr_in channel;

    memset(&channel, 0, sizeof(channel));
    channel.sin_family = AF_INET;
    channel.sin_addr.s_addr = htonl(INADDR_ANY);
    channel.sin_port = htons(SERVER_PORT);

    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock < 0)
        fatal("tworzenie gniazda nie powiodlo sie");
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on));

    if (bind(sock, (struct sockaddr *)&channel, sizeof(channel)) < 0)
        fatal("nie powiodla sie operacja bind");

    if (listen(sock, QUEUE_SIZE) < 0)
        fatal("nie powiodla sie operacja listen");

    while (true)
    {
        consock = accept(sock, 0, 0);
        if (consock < 0)
            fatal("nie powiodla sie operacja accept");

        read(consock, buf, BUF_SIZE);

        fdesc = open(buf, O_RDONLY);
        if (fdesc < 0)
            fatal("blad otwarcia pliku");

        while ((fbytes = read(fdesc, buf, BUF_SIZE)) > 0)
            write(consock, buf, fbytes);

        close(fdesc);
        close(consock);
    }
    return 0;
}

void fatal(char *message)
{
    printf("%s\n", message);
    exit(1);
}