/******************************************************************************
 * filename: utility_sys.h
 * Written by: James Ross
 *****************************************************************************/

#ifndef _UTL_SYS_H_
#define _UTL_SYS_H_

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/times.h>
#include <sys/wait.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <errno.h>
#include <assert.h>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>

#include "./convNum/convNum.h"       /* str to int functions */
#include "./err_handle/err_handle.h" /* general error printing */

/* Allocate an input buffer with a '\0' terminatior at the end.
   If nothing is read, buff[0] = '\0'.      
   - fd    == int   , File descriptor used for allocInputBuff()
   - buff  == char* , Buffer to be filled with character data from fd.
   - nbyte == size_t, number of bytes to read 
   - retBytes == ssize_t, number of bytes read from file
                    (typically the size of buffer array) */
#define READ_INPUT(fd, buff, nByte, retBytes)                                  \
{                                                                              \
    assert(buff != NULL);                                                      \
    if((retBytes = read(fd, (void*) buff, nByte)) == -1)                       \
        errExit("READ_INPUT, read() failure");                                 \
} /* end READ_INPUT */

/* Copy a variable ammount of characters from a buffer based on a given 
   position.
   Place resulting string in resStr based on a given conditional. 
   resStr will be '\0' terminated.
   NOTE: Typically used in specific steps or in a while loop. 
   - fd     == int  , File descriptor corresponding to inBuf.
   - inBuf  == char*, buffer to copy from. Must not be NULL.
   - bfPl   == char*, the current location inside inBuf. (init: bfPl = inBuf
   - resStr == char*, buffer to copy to.
   - nbyte  == size_t, number of bytes to read
   - conditional == The conditionals desired in the copy process.
                  Example: inBuf[i] != ' ' && inBuf[i] != '\n'
   - retBytes == number of bytes returned when READ_INPUT is called */
#define READ_PARSE(fd, inBuf, bfPl, nByte, resStr, conditional, retBytes)      \
{                                                                              \
    int _TM_ = 0;                                                              \
    assert(resStr != NULL && bfPl != NULL && inBuf != NULL);                   \
                                                                               \
    for(_TM_ = 0; conditional; ++_TM_)                                         \
    {                                                                          \
        resStr[_TM_] = *bfPl;                                                  \
        ++bfPl;                  /* increase buff placement */                 \
        if(*bfPl == '\0'){   /* reached end of current buffer */               \
            READ_INPUT(fd, inBuf, nByte, retBytes);                            \
            inBuff[retBytes] = '\0';                                           \
            bfPl = inBuf;                                                      \
        }                                                                      \
    } /* end for */                                                            \
                                                                               \
    if(*(bfPl) == '\n'){                                                       \
        resStr[_TM_] = '\n';                                                   \
        ++(bfPl);  /* increment over '\n' */                                   \
    }                                                                          \
} // end READ_NEXT_FILE

#endif
/************ EOF **************/
