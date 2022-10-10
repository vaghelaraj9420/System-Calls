#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>

void run_cmd(char *cmd, int* fd_in, int* fd_out)
{
    int c = fork();

    if (c==0)
    {
        if (fd_in != NULL)
        {
            close(fd_in[1]);
            dup2(fd_in[0], 0);
        }
        if (fd_out != NULL)
        {
            close(fd_out[0]);
            dup2(fd_out[1],1);
        }
        execlp(cmd, cmd, NULL);
    }
}

int main(int argc, char **argv)
{
    int fd_1[2], fd_2[2], i;
    pipe(fd_1);
    pipe(fd_2);

    run_cmd(argv[1], NULL, fd_1);

    for( i=2; i<argc-1; i++)
    {
        if (i%2 == 0)
            run_cmd(argv[i], fd_1, fd_2);
        else
            run_cmd(argv[i], fd_2, fd_1);
    }
    if (i%2 == 0)
        run_cmd(argv[i], fd_1, NULL);
    else
        run_cmd(argv[i], fd_2, NULL);
}