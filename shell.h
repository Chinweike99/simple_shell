#ifndef _SHELL_H
#define _SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>

#define BUFSIZE 1024
#define TOK_BUFSIZE 128

typedef struct data
{
	char **av;
	char *str;
	int count;
	char **args;
	int stat;
	char *pid;
	char **_environ;
} dataShell;

/**
 * struct _linked_list - single linked list
 * @isolator: ; | &
 * @next: next node
 * Description: single linked list to store separators
 */
typedef struct _linked_list
{
	char isolator;
	struct _linked_list *next;
} _linkedlist;

/**
 * struct _track_list - single linked list
 * @track: command line
 * @next: next node
 * Description: single linked list to store command lines
 */
typedef struct _track_list
{
	char *track;
	struct _track_list *next;
} _tracklist;

/**
 * struct _single_list - single linked list
 * @varlen: length of the variable
 * @value: value of the variable
 * @lenVal: length of the value
 * @next: next node
 * Description: single linked list to store variables
 */
typedef struct _single_list
{
	int varLen;
	char *value;
	int lenVal;
	struct _single_list *next;
} singlelist;

/**
 * struct builtin_s - Builtin struct for command args.
 * @name: The name of the command builtin i.e cd, exit, env
 * @f: data type pointer function.
 */
typedef struct builtin_s
{
	char *ename;
	int (*f)(dataShell *data);
} builtint;


/*******STRING 1 UTILS*******/

int _strspn(char *str, char *accbytes);
int _strcmp(char *str1, char *str2);
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, const char *src);
char *_strchr(char *str, char c);

/*******STRING 2 UTILS ********/
char *_strdup(const char *str);
int _strlen(const char str);
int cmpChars(char str[], const char *delim);

/******STRING  3 UTILS******/
char *_strtok(char str[], const char *delim);
int _isdigit(const char *str);
void revString(char *str);

/*******STDLIBUTIL******/
int getLen(int m);
char *_itoa(int m);
int _atoi(char *str);

/********LOOP ********/
void shellLoop(dataShell *data);
char *noComment(char *inStr);

/*****re_variable********/
char *readLine(int *eof);

/********rep_variable******/
char *replaced_str(singlelist **head, char *str, char *new_str, int nlen);
char *repVar(char *str, dataShell *data);
int varCheck(singlelist **hd, char *inp, char *st, dataShell *data);
void envCheck(singlelist **hd, char *inp, dataShell *data);

/*********memUtils********/
void _memcpy(void *destptr, const void *srcptr, unsigned int size);
void *realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **_realloc2(char **ptr, unsigned int old_size, unsigned int new_size);

/********shell.c*********/
void setData(dataShell *data, char **av);
void freeData(dataShell *data);

/***********splitted.c********/
char **lineSplit(char *str);
int splitCmd(dataShell *data, char str);
char *swapChar(char *str, int bool);
void addNodes(_linkedlist **head_s, _tracklist **head_l,char *str);
void goNext(_linkedlist **list_s, _tracklist **list_l, dataShell *data);

/********UTILITY1********/
void helpEnv(void);
void helpSetenv(void);
void helpUnsetenv(void);
void helpGeneral(void);
void helpExit(void);

/*******UTILITY2********/
void auxhelp(void);
void helpalias(void);
void helpcd(void);


/********changePD********/
void changeDir(dataShell *data);
void cdInto(dataShell *data);
void cdPrevious(dataShell *data);
void cdHome(dataShell *data);

/*******childD*******/
int ccDir(dataShell *data);
int colCheck(char *myPath, int *x);
char *locate(char *cmd, char **_environ);
int ifexecutable(dataShell *data);
int verifyPermit(char *direct, dataShell *data);
int execCmd(dataShell *data);

/********findBuiltin*****/
int findBuilt(dataShell *data);
int shellExit(dataShell *data);
int (*getBuiltin(char *cmd))(dataShell *);
/***********getError********/
int getError(dataShell *data, int val);

/********getHelp***********/
int getHelp(dataShell *data);

/************getLine*******/
void assignLine(char **ptr, size_t *v, char *buff, size_t y);
ssize_t getLine(char **ptr, size_t *v, FILE *stream);
void _callp(int cals);

/***********HandleEnviron1*******/
int cmpName(const char *env1, const char *ename);
ar *getEnv(const char *ename, char **_environ);
int envVar(dataShell *data);

/**********handleEnvironment2******/
char *infoCopy(char *ename, char *value);
void setEnv(char *ename, char *value, dataShell *data);
int envSet(dataShell *data);
int delEnv(dataShell *data);

/********handleError********/
char *strmsg(dataShell *data, char *mes, char *error, char *verstr);
char *errorMsg(dataShell *data);
char *unFound(dataShell *data);
char *errorShell(dataShell *data);

/*******handleError2*********/
char *errorEnv(dataShell *data);
char *pathError(data_shell *datash);

/***********listOperation**********/
_linkedlist *sepEnd(_linkedlist **head, char item);
void freeList(_linkedlist **head);
_tracklist *addcmd(_tracklist **head, char *track);
void freeLi(_tracklist **head);

/**********checkSyntax*************/
int charRepeated(char *str, int x);
int findError(char *str, int x, char last);
int findChar(char *str, int *x);
void printError(dataShell *data, char *str, int x, int bol);
int checkSyntax(dataShell *data, char *str);



#endif
