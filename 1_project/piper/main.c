/*******************************************************************************
 * filename: main.c
 *
 * This program will take input from stdin and pass the input to a child
 * process which will remove ever instance of the character 'p' out of the
 * input and write the result.
 *
 * written by: James Ross
 ******************************************************************************/

#include "piper.h"

int main(int argc, char *argv[])
{
    
    if(argc > 1) noerrExit("Invalid arguments, $cmd");

    stdinToOut_remChar('q');

    exit(EXIT_SUCCESS);
}//end main

/************** EOF **************/
