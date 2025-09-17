#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 9000

int main()
{
    int sockfd, newsock;
    struct sockaddr_in serv, cli;
    socklen_t len = sizeof(cli);
    char buf[1024];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = INADDR_ANY;
    serv.sin_port = htons(PORT);

    bind(sockfd, (struct sockaddr *)&serv, sizeof(serv));
    listen(sockfd, 5);

    while (1)
    {
        newsock = accept(sockfd, (struct sockaddr *)&cli, &len);
        int n;
        while ((n = read(newsock, buf, sizeof(buf))) > 0)
        {
            write(newsock, buf, n);
        }
        close(newsock);
    }
    return 0;
}
