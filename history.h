#ifndef HISTORY_H
#define HISTORY_H

#define HISTORY 20

typedef long long int ll;

void dohistory(char * home_directory);
int gethistoryfirst(char history[HISTORY][100], int * numofcommands, int fd);
void gethistory(char history[HISTORY][100], char *historypath, char * a, int* historyindex, int*numofcommands);

#endif