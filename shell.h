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
