#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
main()
{
    int fd[2], n = 0, i;
    pipe(fd);
    if (fork() == 0)
    { /* Child process */
        close(1);
        dup(fd[1]); /* Redirect the stdout of this process to the pipe. */
        close(fd[0]);
        for (i = 0; i < 10; i++)
        {
            printf("%d\n", n);
            n++;
        }
    }
    else
    { /* Parent process */
        close(0);
        dup(fd[0]); /* Redirect the stdin of this process to the pipe */
        close(fd[1]);
        for (i = 0; i < 10; i++)
        {
            scanf("%d", &n);
            printf("n = %d\n", n);
            sleep(1);
        }
    }
}