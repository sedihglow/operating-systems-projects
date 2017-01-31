/*******************************************************************************
 * filename: piper.c
 *
 * Implements the functions defined in piper.h and its helper functions.
 *
 * Written by: James Ross
 ******************************************************************************/

#include "piper.h"

/******************* STATIC PROTOTYPES ****************************************/
static void takeInput(int pipeFD);
static void processPipe(int pipeFD, char toRemove);

/****************** STATIC FUNCTIONS ******************************************/
static void takeInput(int pipeFD)
{
    char inBuff;
    ssize_t retBytes;

    do{
        /* get data from STDIN */
        READ_INPUT(STDIN_FILENO, &inBuff, sizeof(inBuff), retBytes);

        /* write to pipe */
        if(retBytes == RW_END) break; // stops an extra newline

        if(FAIL == write(pipeFD, &inBuff, sizeof(inBuff)))
            errExit("takeInput, write() failure");
    }while(retBytes != RW_END);
}//end takeInput

static void processPipe(int pipeFD, char toRemove)
{
    char inBuff;      /* byte used in byte stream of pipe */
    ssize_t retBytes;

    do{
        /* get data from pipe */
        READ_INPUT(pipeFD, &inBuff, sizeof(inBuff), retBytes);

        /* check for char to Remove */
        if(toRemove != inBuff){
            if(FAIL == write(STDOUT_FILENO, &inBuff, sizeof(inBuff)))
                errExit("processPipe, write() failure");
        }
    }while(retBytes != RW_END);
}//end processPipe

/***************** HEADER FUNCTIONS *******************************************/
void stdinToOut_remChar(char toRemove)
{
    int pipeFD[2];
    pid_t childPID;

    /* connect the pipe file descriptors */
    if(FAIL == pipe(pipeFD)) errExit("stdinToOut_remChar, pip() failure");

    switch(childPID = fork()){
        case -1: errExit("stdinToOut_remChar(), fork failure"); break;
        case  0: /* child */
            if(FAIL == close(pipeFD[P_WR])) errExit("close():child P_WR fail");
            processPipe(pipeFD[P_RD], toRemove); // print all but toRemove
            if(FAIL == close(pipeFD[P_RD])) errExit("close():child P_RD fial"); 
            exit(EXIT_SUCCESS);
            break;
        default: /* parent */
            if(FAIL == close(pipeFD[P_RD])) errExit("close() P_RD fail"); 
            takeInput(pipeFD[P_WR]); // take input stdin, write to pipe
            if(FAIL == close(pipeFD[P_WR])) errExit("close():child P_WR fail");
            wait(NULL);
    }
}//end stdinToOut_remChar
