#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
main()
{
    execlp("cal", "cal", "2001", NULL);
    printf("This statement is not executed if execlp succeeds.\n");
}
