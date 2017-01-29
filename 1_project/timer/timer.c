/******************************************************************************
 * filename: timer.c
 *
 * Implements the functions declared in timer.h and its helper functions
 *
 * written by: James Ross
 *****************************************************************************/

#include "timer.h"

#define FAIL -1

processTime_s getProcessTime(char *progPath, char **args, char **envp)
{
    struct tms startTMS;
    struct tms endTMS;
    processTime_s result;
    clock_t userClkTime;
    clock_t sysClkTime;
    pid_t childPid;
    long clkTicks = sysconf(_SC_CLK_TCK); // gets systems clock tick rate

    if(NULL == progPath) errExit("Invalid program path");

    // get USER and SYS times up to this point
    if(FAIL == times(&startTMS)) errExit("getProcessTime(), times() failure");
    
   
    switch(childPid = fork()){
        case -1: errExit("getProccessTime: fork() failure"); break;
        case 0 : execve(progPath, args, envp);                break;
        default: wait(NULL);
    }
    // get USER and SYS times after program execution to be measured
    if(FAIL == times(&endTMS)) errExit("getProcessTime(), times() failure");

    // get the difference between the times found with times()
    userClkTime = endTMS.tms_utime;// - startTMS.tms_utime;
    sysClkTime  = endTMS.tms_stime;// - startTMS.tms_stime;
    
    /* convert the clock ticks measured by times() to seconds by dividing
     * by the number of clock ticks per second. This can be found by the
     * function sysconf() */
    result.userTimeSec = userClkTime;///clkTicks;
    result.sysTimeSec  = sysClkTime;///clkTicks;

    return result;
} //end getProcessTime
