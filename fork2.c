#include <stdio.h>
#include <sys/ipc.h>
main()
{
    int i, x = 10, pid1, pid2;
    printf("Before forking, the value of x is %d\n", x);
    if ((pid1 = fork()) == 0)
    { /* First child process */
        for (i = 0; i < 5; i++)
        {
            printf("\t\t\t At first child: x= %d\n", x);
            x = x + 10;
            sleep(1); /* Sleep for 1 second */
        }
    }
    else
    { /* Parent process */
        if ((pid2 = fork()) == 0)
        { /* Second child */
            for (i = 0; i < 5; i++)
            {
                printf("\t\t\t\t\t\t At second child: x= %d\n", x);
                x = x + 20;
                sleep(1); /* Sleep for 1 second */
            }
        }
        else
        { /* Parent process */
            waitpid(pid1, NULL, 0);
            waitpid(pid2, NULL, 0);
            printf("Both children terminated\n");
        }
    }
}