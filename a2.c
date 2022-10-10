#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <unistd.h>
#define BUFSIZE 100

int main(int argc, char* argv[])
{
    int fd[2];
    pipe(fd);       // Initializing the pipe
    int i,count=0;

    int pid;

    // for(int i=0;i<argc;i++)
    //     printf("%s ", argv[i+1]);
    if((pid = fork()) == 0)
    {
        close(1);
        close(fd[0]);       // The left child will not read
        dup(fd[1]);         // The left child stdout redirected to the pipe

        // for(i=1;i<argc;i++)
        // {
        //     if(argv[i] != '|')
        //         count++;
        // }
        if(argv[2] != '|')
            execlp(argv[1], argv[1], NULL);     // left child Executes the first command
        else if(argv[2] == '|')
            execlp(argv[1], argv[1], argv[2], NULL); 
    }
    if((pid = fork()) == 0)
    {
        close(0);
        close(fd[1]);       // The right child will not write
        dup(fd[0]);         // The right child stdin redirected to the pipe

        if(argv[3] == NULL)
            execlp(argv[2], argv[2], NULL);     // right child Executes the second command
        else if(argv[3] != NULL)
            execlp(argv[2], argv[2], argv[3], NULL); 

    }
    close(fd[0]);
    close(fd[1]);

    return 0;


}