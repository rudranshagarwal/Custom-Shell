#include "foreground.h"
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <wait.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

extern int fg;
extern int fgpid;
extern char fname[100];
extern int fnumber;

long int foreground(char *command)
{
    int *status;
    char *args[20];
    char *parameter = strtok(command, "\t\n>< ");
    ll i = 0;
    while (parameter != NULL)
    {
        args[i] = (char *)malloc(strlen(parameter) + 1);
        strcpy(args[i++], parameter);
        parameter = strtok(NULL, "\t\n>< ");
    }
    args[i] = NULL;
    time_t begin = time(NULL);
    int forkReturn = fork();
    if (forkReturn < 0)
    {
        printf("Process making unsuccessful\n");
    }
    if (forkReturn == 0)
    {
        errno = 0;
        execvp(args[0], args);
        if (errno == 2)
        {
            printf("Invalid command\n");
        }
        else
        {
            perror("");
        }

        errno = 0;
        return -1;
    }
    else
    {
        fgpid = forkReturn;

        waitpid(forkReturn, status, 0);
        time_t end = time(NULL);
        return (end - begin);
    }
}