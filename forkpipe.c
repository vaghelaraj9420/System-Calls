#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#define BUFFSIZE 100

char line[BUFFSIZE];
char *argv[BUFFSIZE];

void get_cmd(){
	// get command from user
	printf("Shell>\t");
	fgets(line, BUFFSIZE, stdin);
	// remove trailing newline
	if ((strlen(line) > 0) && (line[strlen (line) - 1] == '\n'))
        line[strlen (line) - 1] = '\0';
	//printf("%s\n", line);
}

void convert_cmd(){
	// split string into argv
	char *ptr;
    int i;
	i = 0;
	ptr = strtok(line, " ");
	while(ptr != NULL){
		//printf("%s\n", ptr);
		argv[i] = ptr;
		i++;
		ptr = strtok(NULL, " ");
	}

	// check for "&"
	if(!strcmp("&", argv[i-1])){
	argv[i-1] = NULL;
	argv[i] = "&";
	}else{
	argv[i] = NULL;
	}
}

int main()
{
    int fd[2];
    pipe(fd);       // Initializing the pipe

    int pid;
    

    // if((pid=fork()) == 0)           // Child 1
    // {
        while(1)                        // Shell scripting starts
        {
            // get the command from user
		    get_cmd();

            if(strcmp(line, "") == 0)
                continue;                   // Bypass empty commands
            else if(strcmp(line, "exit") == 0)
                break;                          // break if exit is written
            else{
                // fit the command into *argv[]
		        convert_cmd();
                
                // close(1);
                // close(fd[0]);       // The first child will not read
                // dup(fd[1]);         // The first child stdout redirected to the pipe
                // write(fd[1], line, strlen(line) +1);        // write the command onto the pipe

                if(fork() == 0)             // second child will execute the command using execlp
                {
                    // close(fd[1]);       // The second child will not write
                    // dup(fd[0]);         // The second child stdin redirected to the pipe      
                    // read(fd[0], line, strlen(line) + 1);        // Reading the command from the pipe
                    // char* token = strtok(line, " ");
                    
                    if(!strcmp(argv[0], "ls") || !strcmp(argv[0], "pwd") || !strcmp(argv[0], "cd") || !strcmp(argv[0], "mkdir"))
                        // execlp(token, token, NULL);
                        execvp(argv[0], argv);
                    else
                        printf("Invalid command");
                }

                continue;
            }
        }
    // }

    return 0;
}