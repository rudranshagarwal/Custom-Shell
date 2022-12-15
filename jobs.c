#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "jobs.h"

extern ll number[100];
extern char backcommand[100][100];
extern int backgroundpid[100];

ll sortednumber[100];
char sortedbackcommand[100][100];
int sortedbackgroundpid[100];