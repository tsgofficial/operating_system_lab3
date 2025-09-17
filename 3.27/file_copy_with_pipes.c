#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <src> <dest>\n", argv[0]);
        return 1;
    }

    int p[2];
    pipe(p);

    pid_t pid = fork();
    if (pid == 0)
    {
        // Child: read from pipe, write to dest file
        close(p[1]);
        int out = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        char buf[1024];
        int n;
        while ((n = read(p[0], buf, sizeof(buf))) > 0)
        {
            write(out, buf, n);
        }
        close(out);
        exit(0);
    }
    else
    {
        // Parent: read src file, write to pipe
        close(p[0]);
        int in = open(argv[1], O_RDONLY);
        char buf[1024];
        int n;
        while ((n = read(in, buf, sizeof(buf))) > 0)
        {
            write(p[1], buf, n);
        }
        close(in);
        close(p[1]);
        wait(NULL);
    }
    return 0;
}
