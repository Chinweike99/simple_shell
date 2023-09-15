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
char *replaced_str(r_var **head, char *str, char *new_str, int nlen);
char *repVar(char *str, dataShell *data);
int varCheck(r_var **hd, char *inp, char *st, dataShell *data);
void envCheck(r_var **hd, char *inp, dataShell *data);

/*********memUtils********/
void _memcpy(void *destptr, const void *srcptr, unsigned int size);
void *realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **_realloc2(char **ptr, unsigned int old_size, unsigned int new_size);

/********shell.c*********/
void setData(dataShell *data, char **av);
void freeData(dataShell *data);


#endif
