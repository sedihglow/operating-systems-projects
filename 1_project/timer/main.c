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
#define MICROSEC_CONV_FACTOR 1000000

int32_t main(int32_t argc, char *argv[], char* envp[])
{
#define BUFF 128
#define P_BUFF 256
    struct timespec *timeResult;   // time of program to execute
    int32_t fd;                    // used to test if command exists
    char sec[BUFF] = {'\0'};
    char nano[BUFF] = {'\0'};
    char toPrint[P_BUFF] = {'\0'}; // final string to print

    if(argc < 2) noerrExit("Invalid number of arguments,"
                           "$cmd progPath progArgs1 ...");

    /* check program path */
    if(FAIL == (fd = open(argv[1], O_RDONLY))) 
        noerrExit("Invalid path to progPath, $cmd progPath progArgs1 ...");
    else close(fd);

    timeResult = getProcessTime(argv[1], argv+1, envp);

    snprintf(sec, BUFF, "%ld", timeResult -> tv_sec);
    snprintf(nano, BUFF, "%ld", timeResult -> tv_nsec);
    snprintf(toPrint, P_BUFF, "%s seconds and %s nano seconds\n", sec, nano);

    write(STDOUT_FILENO, toPrint, strlen(toPrint));

    free(timeResult);
    exit(EXIT_SUCCESS);
#undef BUFF
}
