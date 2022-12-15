#include "background.h"
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <wait.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

extern ll number[100];
extern char backcommand[100][100];
extern int backgroundpid[100];

void backgrounddone()
{
    int status;

    int pid = waitpid(-1, &status, WNOHANG);
    ll i;
    if (pid > 0)
    {
        if (WIFSTOPPED(status))
            return;
        for (i = 0; i < 100; i++)
        {

            if (backgroundpid[i] == pid)
                break;
        }
        if(i >= 100)
            return;
        // assert(1 == 2);
        if (WIFEXITED(status))
        {
            char buf[200];
            sprintf(buf, "[%lld] %s with pid = %d exited normally\n", number[i], backcommand[i], backgroundpid[i]);
            write(2, buf, strlen(buf));
            number[i] = 0;
            backgroundpid[i] = -1;
            for (ll j = 0; j < strlen(backcommand[i]); j++)
            {
                backcommand[i][j] = '\0';
            }
        }
        else
        {
            char buf[200];
            sprintf(buf, "[%lld] %s with pid = %d exited abnormally\n", number[i], backcommand[i], backgroundpid[i]);
            write(2, buf, strlen(buf));
            number[i] = 0;
            backgroundpid[i] = -1;
            for (ll j = 0; j < strlen(backcommand[i]); j++)
            {
                backcommand[i][j] = '\0';
            }
        }
    }
    errno = 0;
}

void background(char *command, ll n)
{

    // printf    // printf("%s\n", execcommand);
    int forkReturn = fork();
    char printarguement[100];

    number[n - 1] = n ;
    char *args[20];
    char *parameter = strtok(command, "\t\n>< ");
    ll num_of_args = 0;
    while (parameter != NULL)
    {
        args[num_of_args] = (char *)malloc(strlen(parameter) + 1);
        strcpy(args[num_of_args++], parameter);
        // printf("%s\n", args[i]);
        parameter = strtok(NULL, "\t\n>< ");
    }
    args[num_of_args] = NULL;
    // printf("[%lld] %d\n", n, getpid());
    errno = 0;
    strcpy(printarguement, args[0]);

    backgroundpid[n - 1] = forkReturn;
    if(forkReturn < 0)
    {
        printf("Process making unsuccessful\n");
    }

    else if (forkReturn == 0)
    {
        setpgid(0,0);
        if (execvp(args[0], args) < 0)
        {
            printf("%s Invalid command\n", args[0]);
            exit(1);
        }
    }
    else
    {
        int *status;
        char pidstatus[100];
        sprintf(pidstatus,"[%lld] %d\n", n, forkReturn);
        write(2,pidstatus, strlen(pidstatus));
    }
}