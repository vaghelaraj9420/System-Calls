#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <sys/ipc.h>
#include <unistd.h>
#define BUFSIZE 100




int main()
{
   
 int i, pid, fd[2];
    char line[BUFSIZE]; // string for storing the gs comaands
    int a, b, c, d;
    char w[10], x[10], y[10], z[10];
    char strA[10], strB[10], strC[10], strD[10];
    int ans;

    pipe(fd); // fd[0] is for reading, fd[1] is for writing

   // Redirect the stdout of A to the pipe


    if (fork() == 0) // Child process, B
      {
            close(0);
          dup(fd[0]);   // Redirect the stdin of B to the pipe
          close(fd[1]); // B will not write

          // Read the string from the pipe
         // sscanf(line, "%d %d %s %d %d %s %s %s", &a, &b, w, &c, &d, x, y, z);
          // sprintf(strA, "%d", a);
          // sprintf(strB, "%d", b);
          // sprintf(strC, "%d", c);
          // sprintf(strD, "%d", d);

          // Execute the gs command using execlp()
          // execlp("gs", "gs", "-c", strA, strB, w, strC, strD, x, y, z, NULL);
          execlp("gs", "gs", NULL);
      }
      else{
     while(1)
    {
      printf("Enter the two coordinates for drawing the line in GhostScript:\n");
      scanf("%d", &a);
      scanf("%d", &b);
      scanf("%d", &c);
      scanf("%d", &d);

      // if(isdigit(a))
      // {
      //   printf("\nEntered input is not valid");
      //   break;
      // }
      // Print the line string into the pipe
      sprintf(line, "%d %d %s %d %d %s %s %s\n", a, b, "moveto", c, d, "lineto", "closepath", "stroke");
      // sprintf(line,"%d %d moveto %d %d lineto closepath stroke\n",a,b,c,d);
        write(fd[1], line, strlen(line) +1);

      // if(!strcmp(line, "quit"))
      //   return 1;

     
       printf("Want to draw anymore lines? (0/1)");
       scanf("%d", &ans);
       if(ans!=1)
         break;
    }
      }
   
    return 0;
}
