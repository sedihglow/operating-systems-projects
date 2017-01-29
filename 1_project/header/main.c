/******************************************************************************
 * Project 1 - header
 *
 * Program will take the arguments of filename and a number.
 * Filename will be the file to read.
 * The number will write the represent the first N lines of the file.
 *
 * Program will print N lines of a file, if N is zero, the first line will be
 * printed.
 *
 * Written by: James Ross
 ******************************************************************************/

#include "header.h"


// $cmd filename numberOfLinesToPrint
int32_t main(int32_t argc, char *argv[])
{
#define DFLT_PL 1 // default number of lines to print
    uint32_t num = DFLT_PL;

    if(argc > 3) noerrExit("Too many arguments, $cmd file num\n");

    if(argc < 2) noerrExit("Not enough arguments, $cmd file num\n");

    if(argc == 3) num = convU32_t(argv[2], GN_NONEG | GN_BASE_10, "print lines");

    printLines(argv[1], num);

     
    exit(EXIT_SUCCESS);
#undef DFLT_PL
}
/************ EOF **************/
