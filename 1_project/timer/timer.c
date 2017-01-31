/******************************************************************************
 * filename: timer.c
 *
 * Implements the functions declared in timer.h and its helper functions
 *
 * written by: James Ross
 *****************************************************************************/

#include "timer.h"


struct timespec* getProcessTime(char *progPath, char **args, char **envp)
{
    struct timespec startTime;
    struct timespec stopTime;
    struct timespec *resultTime;
    pid_t childPid;

    if(NULL == progPath) errExit("Invalid program path");

    switch(childPid = fork()){
        case -1: errExit("getProccessTime: fork() failure"); break;
        case 0 : /* child */
                 execve(progPath, args, envp);               break;
        default: /* parent */
                 clock_gettime(CLOCK_REALTIME, &startTime);
                 wait(NULL);
                 clock_gettime(CLOCK_REALTIME, &stopTime);
    }

    resultTime = (struct timespec*)malloc(sizeof(struct timespec*));
    if(NULL == resultTime) 
        errExit("getProcessTime: resultTime, malloc failure");
    
    // store length waited in seconds and nano seconds
    TIMESPEC_SUB(&stopTime, &startTime, resultTime);

    return resultTime;
} //end getProcessTime
