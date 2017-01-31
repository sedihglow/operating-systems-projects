/*******************************************************************************
 * filename: main.c
 *
 *  This program will print hello every 2 seconds, exits after 10 seconds,
 *  counts the ammounts of ctrl+c signals are sent and prints the value.
 *
 * written by: James Ross
 ******************************************************************************/

#include "signaler.h"

int main(int argc, char *argv[])
{
#define P_BUFF 128
    int32_t sigIntCount;
    char toPrint[P_BUFF] = {'\0'};

    if(argc != 1) noerrExit("Invalid number of arguments. $cmd");

    sigIntCount = countDown(); // returns the ammount of times ctrl+c was sent

    snprintf(toPrint, P_BUFF, "Total count of ctrl+c during countdown: %d\n", 
             sigIntCount);

    /* print ammount of ctrl+c */
    write(STDOUT_FILENO, toPrint, sizeof(toPrint));

    exit(EXIT_SUCCESS); 
#undef P_BUFF
}
