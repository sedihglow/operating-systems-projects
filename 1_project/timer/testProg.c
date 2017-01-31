/* test program to pass into timer, for testing */

#include <stdio.h>
#include <stdlib.h>

// $cmd NumOfLoops
int main(int argc, char* argv[]){
    long long i;
    long long stop = atoi(argv[1]);
    long long junk = 0;
    
    if(argc == 1) return 0;
    
    for(i = 0; i < stop; ++i){
        junk += 1;
        junk *= 2;
        junk *= -1;
        if(i%8) junk /= 4;
    }
    return 0;
}
