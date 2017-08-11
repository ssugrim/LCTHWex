/* Compile with:
export CFLAGS="-g -Wall -std=gnu11 -O3"  #the usual.
make curly
*/
#include <stdio.h>

int main(){
    int out =1;
    int total = 0;
    int max = 5;
    for (int i=0; i<= max; i++){    
        total += i;                 
    }                               
    printf("out= %i, original total=%i \n", out, total);
}
