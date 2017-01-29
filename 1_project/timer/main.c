/******************************************************************************
 * filename: main.c
 *
 * Takes a program name as an argument, displays the time it took for the
 * program to execute in USER time and SYS time.
 *
 * Utilizes the system call times()
 * see man 2 times()
 *
 * written by: James Ross
 *****************************************************************************/

#include "timer.h"

int32_t main(int32_t argc, char *argv[], char* envp[])
{
    processTime_s timeResults;

    if(argc < 2) noerrExit("Invalid number of arguments,"
                           "$cmd progPath progArgs1 ...");
    timeResults = getProcessTime(argv[1], argv+1, envp); 

    write(STDOUT_FILENO, &(timeResults.userTimeSec), sizeof(double));
    write(STDOUT_FILENO, &(timeResults.sysTimeSec), sizeof(double));
    exit(EXIT_SUCCESS);
}
