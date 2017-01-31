/******************************************************************************
 * filename: timer.h
 *
 * Defines the functions required to run a program and time its execution.
 *
 * Utilizes the system call times()
 * 
 * Written by: James Ross
 *****************************************************************************/

#include "../utility_sys.h"

struct timespec* getProcessTime(char *progPath, char **args, char **envp);
