/******************************************************************************
 * filename: header.c
 * Implementation of printLines and all functions required to accomplish
 * printLines function
 *
 * written by: James Ross
 */

#include "header.h"

#define IN_BUFF 11
#define FAIL -1

/******************************************************************************
 *                          static prototypes
 *****************************************************************************/
 
 /*
  * fd = file descriptor
  * inBuff = input buffer to fill with read data
  * bfPl = Ptr to inBuff to keep track of place in buffer while parsing
  *
  * Returns: - File is empty: NULL
  *          - if not empty: next line from file
  */
static char* readLinesFromFile(int32_t fd, char *inBuff, char** bfPl);

/******************************************************************************
 *                          static functions
 *****************************************************************************/
static char* readLinesFromFile(int32_t fd, char *inBuff, char** bfPl){
#define TO_READ 10
#define RES_BUFF 512
#define EMPTY_FILE 0
    ssize_t retBytes = 0;   // number of bytes read from file
    size_t nByte = TO_READ; // number of bytes to read
    size_t strLen = 0;      // holds length of resultStr data
    char *retStr = NULL;    // final string to return
    char resultStr[RES_BUFF] = {'\0'}; // string resulting from parse

    assert(inBuff != NULL &&  *bfPl != NULL);
    
    if('\0' == **bfPl){ // initial read before parsing if not already done
            READ_INPUT(fd, inBuff, nByte, retBytes);
            if(EMPTY_FILE == retBytes) return NULL;
            inBuff[retBytes] = '\0';
            *bfPl = inBuff;
    }

    READ_PARSE(fd, inBuff, *bfPl, nByte, resultStr, 
              (**bfPl != '\n') && (strlen(resultStr) != RES_BUFF-1), retBytes);

    strLen = strlen(resultStr);
    retStr = malloc(sizeof(char)*strLen+1);
    if(NULL == retStr) errExit("readLinesFromFile(), malloc() failure, retstr");

    strncpy(retStr, resultStr, strLen);
    retStr[strLen] = '\0';

    return retStr;

#undef TO_READ
#undef RES_BUFF
#undef EMPTY_FILE
}//end readFromFile

/******************************************************************************
 *                          header functions
 *****************************************************************************/
size_t printLines(char *path, uint32_t numToPrint){
    char *printStr = NULL; // string to write to stdout
    char *bfPl = NULL;     // position inside of inBuff
    uint32_t nlCount = 0;   // number of new lines printed
    int32_t fd;
    char inBuff[IN_BUFF] =  {'\0'}; // input buffer for read
     

    bfPl = inBuff;

    if(FAIL == (fd = open(path, O_RDONLY)))
        errExit("printLines(), open() failure");

    do{

        printStr = readLinesFromFile(fd, inBuff, &bfPl);

        /* check if EOF reached. empty file || linux text file indicator '\n'
         * unless file is empty, linux text files end in a single '\n' */
        if(NULL == printStr || (inBuff[0] == '\n' && inBuff[1] == '\0')) break; 

        if(FAIL == write(STDOUT_FILENO, printStr, strlen(printStr)))
            errExit("printLines(), write() failure");
        
        ++nlCount;
    }while(nlCount < numToPrint);

    free(printStr);
   
    return 0;

}
#undef IN_BUFF
/************ EOF **************/
