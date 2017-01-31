/******************************************************************************
 * filename: header.c
 * Implementation of printLines and all functions required to accomplish
 * printLines function
 *
 * written by: James Ross
 */

#include "header.h"

#define FAIL -1



/* TODO: Adjust this macro or make an alternate that can call a function with
         variable arguments, rather than just one argument. (i.e. free(pntr);) */
/* vectorizes a function funct, its C99 as fuck tho.
   -Type is the type of pointer used. (VA_ARGS could be void for example.). 
   -... is a variable argument list.
   -will execute every argument into the function.
   -funct only takes in one argument. */
#define APPLY_FUNCT(type, funct, ...)                                          \
{                                                                              \
    void *stopper = NULL; /* pointer to 0 */                             \
    type **apply_list = (type*[]){__VA_ARGS__, stopper};                       \
    int __i_;                                                                  \
                                                                               \
    for(__i_ = 0; apply_list[__i_] != stopper; ++__i_){                        \
        (funct)(apply_list[__i_]);}                                            \
} /* end apply_funct */
    
/* apply free to every pointer given in the argument list using the
   apply_funct macro */
#define FREE_ALL(...)   APPLY_FUNCT(void, free, __VA_ARGS__)


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
static char* readLinesFromFile(int32_t fd, char *inBuff, int *bfPl);

/******************************************************************************
 *                          static functions
 *****************************************************************************/
static char* readLinesFromFile(int32_t fd, char *inBuff, int *bfPl){
#define TO_READ 10
#define RES_BUFF 512
#define EMPTY_FILE 0
    ssize_t retBytes = 0;   // number of bytes read from file
    size_t nByte = TO_READ; // number of bytes to read
    size_t len = 0;      // holds length of resultStr data
    char *retStr = NULL;    // final string to return
    char resultStr[RES_BUFF] = {'\0'}; // string resulting from parse

    assert(inBuff != NULL &&  bfPl != NULL);
    
    if('\0' == inBuff[*bfPl]){ // initial read before parsing if not already done
            READ_INPUT(fd, inBuff, nByte, retBytes);
            if(EMPTY_FILE == retBytes) return NULL;
            inBuff[retBytes] = '\0';
            *bfPl = 0;
    }

    READ_PARSE(fd, inBuff, *bfPl, nByte, retBytes, resultStr, RES_BUFF-1,
              (inBuff[*bfPl] != '\n'));

    ++(*bfPl);  // increment over '\n'

    len = strlen(resultStr);
    resultStr[len] = '\n'; //place newline in the string, may take last index
    len += 2;              // +1 for '\n', +1 space for a '\0' in retStr

    retStr = (char*)malloc(sizeof(char)*len);
    if(NULL == retStr) errExit("readLinesFromFile(), malloc() failure, retstr");

    strncpy(retStr, resultStr, len-1); // copy all of resultStr
    retStr[len-1] = '\0';              // null at last index of retStr

    return retStr;
#undef TO_READ
#undef RES_BUFF
#undef EMPTY_FILE
}//end readFromFile

/******************************************************************************
 *                          header functions
 *****************************************************************************/
size_t printLines(char *path, uint32_t numToPrint){
#define IN_BUFF 11
    char *printStr = NULL; // string to write to stdout
    uint32_t nlCount = 0;  // number of new lines printed
    int32_t fd = -1;       // initialized to bad FD
    int bfPl = 0;          // position inside of inBuff
    int len = 0;
    char inBuff[IN_BUFF] =  {'\0'}; // input buffer for read
     
    if(FAIL == (fd = open(path, O_RDONLY)))
        errExit("printLines(), open() failure");

    do{

        printStr = readLinesFromFile(fd, inBuff, &bfPl);

        /* check if EOF reached. empty file || linux text file indicator '\n'
         * unless file is empty, linux text files end in a single '\n' */
        if(NULL == printStr || (inBuff[0] == '\n' && inBuff[1] == '\0')) break; 
        
        len = strlen(printStr);
        if(FAIL == write(STDOUT_FILENO, printStr, len))
            errExit("printLines(), write() failure");
        
        ++nlCount;

        free(printStr);
    }while(nlCount < numToPrint);
   
    //FREE_ALL(printStr);
    return 0;
}
#undef IN_BUFF
/************ EOF **************/
