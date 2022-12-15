# ASSUMPTIONS ON LENGHTS AND COMMANDS

COMMAND LENGTH MAX: 100  
MAXIMUM NUMBER OF SEMI-COLONS: 10  
MAXIMUM NUMBER OF ANDS : 10  
MAXIMUM LENGTH OF DIRECTORY/FILE NAMES: 100  
MAXIMUM NUMBER OF PIPED COMMANDS: 1000

SYNTAX ERRORS are shown when inappropriate use of ; and & is used in which case none of the commands is executed.

---

# Compiling and executing

`make`

Make compiles all the files related, namely, shell.c builtin.c, ls.c background.c , foreground.c pinfo.c, discovery.c, history.c and prompt.c

---

# THE PROMPT

username@hostname:directory_name> is the prompt. In case a foreground process takes longer than 1s, even that is added to it. ~ is the directory from which shell is called. In case of directories which are not subdirectories by it, their, absolute address from / is printed.

---

# BUILTIN COMMANDS:

## cd

`cd <directory_name>`

errors are shown when given directory doesn't exist
or too many arguements are given. Use of ~ implies from the directory of shell. Anything from / implies home of the system.

## pwd

`pwd`

address is given from / (system home)

## echo

`echo <message>`

anything inside message is printed as it. Message is of single line. Multiple spaces or tabs are taken as one

---
---

## ls 

`ls <options> <directory-names> <file-names>`

The arguements can be given in any order possible. In case files don't exist, error message will be printed. Files are shown in white, directories in blue and executables in green.

---

## pinfo

`pinfo <pid> `

The pid with 1 doesn't give a correct path directly. If wrong pid is given error is shown. No arguement implies pid of current process is taken

---

## discover

`discover <directory_name> <file_name> <options>`

Colors are printed according to ls. In case file name is not given, all files in the directory are printed. It is assumed that two directory or two files names won't be given.

---

## history

`history`

Last 10 commands entered in the prompt are printed. Blank commands are not counted.

---

# Background and foreground processes

In case of multiple background processes in a single command, each one is numbered starting from 1  
In case a foreground process runs for more than 1 second and there are multiple foreground processes, the time taken by last process is printed.  
After background process is done, its status along with pid and name is outputted.  
In case of invalid background process, appropriate invalid message is printed but the process is assigned an id.  
In case of invalid foreground process, appropraite inavlid message is printed.

MAXIMUM NUMBER OF BACKGROUND PROCESSES: 100

---

# Piping

It is assumed that maximum number of piped commands can be 1000
Valid syntax for pipes is also assumed