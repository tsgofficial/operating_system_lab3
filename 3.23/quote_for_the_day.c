#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 6017
#define QUOTE "Stay hungry, stay foolish.\n"

int main()
{
    int sockfd, newsock;
    struct sockaddr_in serv, cli;
    socklen_t len = sizeof(cli);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = INADDR_ANY;
    serv.sin_port = htons(PORT);

    bind(sockfd, (struct sockaddr *)&serv, sizeof(serv));
    listen(sockfd, 5);

    while (1)
    {
        newsock = accept(sockfd, (struct sockaddr *)&cli, &len);
        write(newsock, QUOTE, strlen(QUOTE));
        close(newsock);
    }
    return 0;
}
