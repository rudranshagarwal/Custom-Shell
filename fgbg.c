#include "fgbg.h"
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern ll number[100];
extern char backcommand[100][100];
extern int backgroundpid[100];

extern int fgthere;
extern int fgpid;
extern char fname[100];
extern int fnumber;

void fg()
{
    char *parameter = strtok(NULL, " \t\n");
    int jobnumber = atoi(parameter);
    int pid;
    ll i;

    for (i = 0; i < 100; i++)
    {
        if (number[i] == jobnumber)
        {
            pid = backgroundpid[i];
            break;
        }
    }
    if (i >= 100)
    {
        printf("Invalid pid\n");
        return;
    }
    strcpy(fname, backcommand[i]);
    fgthere = 1;
    fgpid = pid;
    fnumber = number[i];
    number[i] = 0;
    backgroundpid[i] = -1;
    for (ll j = 0; j < strlen(backcommand[i]); j++)
    {
        backcommand[i][j] = '\0';
    }

    setpgid(pid, getpgid(0));

    signal(SIGTTIN, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);
    
    int status;

    tcsetpgrp(0, pid);

    kill(pid, SIGCONT);

    waitpid(pid, &status, WUNTRACED);

    tcsetpgrp(0, getpgid(0));

    signal(SIGTTIN, SIG_DFL);
    signal(SIGTTOU, SIG_DFL);

    if (WIFEXITED(status) || WIFSTOPPED(status))
    {
        fgthere = 0;
        return;
    }
}

void sig()
{
    char *parameter = strtok(NULL, " ");
    int jobnumber = atoi(parameter);
    parameter = strtok(NULL, " ");
    int y = atoi(parameter);

    int pid;
    ll i;
    for (i = 0; i < 100; i++)
    {
        if (number[i] == jobnumber)
        {
            pid = backgroundpid[i];
            break;
        }
    }
    if (i >= 100)
    {
        printf("Invalid pid\n");
        return;
    }
    if (kill(pid, y) < 0)
    {
        printf("Inavlid sig\n");
        return;
    }
}

void bg()
{
    char *parameter = strtok(NULL, " \t\n");
    int jobnumber = atoi(parameter);
    int pid;
    ll i;

    for (i = 0; i < 100; i++)
    {
        if (number[i] == jobnumber)
        {
            pid = backgroundpid[i];
            break;
        }
    }

    if (i >= 100)
    {
        printf("Invalid pid\n");
        return;
    }

    if (kill(pid, SIGCONT) < 0)
        printf("bg error\n");
}