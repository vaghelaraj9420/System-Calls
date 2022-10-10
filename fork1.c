#include <stdio.h>
#include <sys/ipc.h>
main()
{
    int i;
    if (fork() == 0)
    { /* Child */
        while (1)
        {
            for (i = 0; i < 100000; i++)
                ;
            printf("\t\t\t Child executing\n ");
        }
    }
    else
    { /* Parent */
        while (1)
        {
            for (i = 0; i < 100000; i++)
                ;
            printf("Parent executing\n");
        }
    }
}