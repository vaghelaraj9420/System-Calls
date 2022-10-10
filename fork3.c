#include <stdio.h>
#include <sys/ipc.h>
main()
{
    int x = 0, pid;
    printf("Hello!");
    if ((pid = fork()) == 0)
    { /* Child */
        printf("\nChild:\t Address of x: %x\tValue of x: %d \n", &x, x);
        x = 20;
        printf("Child:\t Address of x: %x\tValue of x: %d \n", &x, x);
    }
    else
    { /* Parent */
        waitpid(pid, NULL, 0);
        printf("\nParent:\t Address of x: %x\tValue of x: %d \n", &x, x);
        x = 10;
        printf("Parent:\t Address of x: %x\tValue of x: %d \n", &x, x);
    }
}