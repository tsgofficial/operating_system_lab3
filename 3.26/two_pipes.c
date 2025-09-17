#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>

int main()
{
    int p1[2], p2[2];
    pipe(p1);
    pipe(p2);

    pid_t pid = fork();
    if (pid == 0)
    {
        // Child: read from p1, write to p2
        close(p1[1]);
        close(p2[0]);
        char buf[1024];
        int n = read(p1[0], buf, sizeof(buf));
        for (int i = 0; i < n; i++)
        {
            if (islower(buf[i]))
                buf[i] = toupper(buf[i]);
            else if (isupper(buf[i]))
                buf[i] = tolower(buf[i]);
        }
        write(p2[1], buf, n);
        exit(0);
    }
    else
    {
        // Parent
        close(p1[0]);
        close(p2[1]);
        char msg[] = "Hi There";
        write(p1[1], msg, strlen(msg));
        char buf[1024];
        int n = read(p2[0], buf, sizeof(buf));
        buf[n] = '\0';
        printf("Modified message: %s\n", buf);
        wait(NULL);
    }
    return 0;
}
