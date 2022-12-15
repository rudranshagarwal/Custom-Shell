#ifndef HELPER_H
#define HELPER_H

typedef long long int ll;

int whichcommand(char * command, char * home_directrory, char * old_directory);
int issyntaxerror(char * b, char ** commands,int i);
ll tokenize(char *s, char **commands, char *delimiter);

#endif