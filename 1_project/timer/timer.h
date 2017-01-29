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

typedef struct{
    double userTimeSec;
    double sysTimeSec;
} processTime_s;

processTime_s getProcessTime(char *progPath, char **args, char **envp);
