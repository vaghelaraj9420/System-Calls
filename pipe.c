#include <stdio.h>
#include <unistd.h> /* Include this file to use pipes */
#define BUFSIZE 80
main()
{
    int fd[2], n = 0, i;
    char line[BUFSIZE];
    pipe(fd); /* fd[0] is for reading, fd[1] is for writing */
    if (fork() == 0)
    {
        close(fd[0]); /* The child will not read */
        for (i = 0; i < 10; i++)
        {
            sprintf(line, "%d", n);
            write(fd[1], line, BUFSIZE);
            printf("Child writes: %d\n", n);
            n++;
            sleep(2);
        }
    }
    else
    {
        close(fd[1]); /* The parent will not write */
        for (i = 0; i < 10; i++)
        {
            read(fd[0], line, BUFSIZE);
            sscanf(line, "%d", &n);
            printf("\t\t\t Parent reads: %d\n", n);
        }
    }
}