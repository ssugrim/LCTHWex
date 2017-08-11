/* Compile with:
export CFLAGS="-g -Wall -std=gnu11 -O3"  #the usual.
make curly
*/
#include <stdio.h>

#define sum(max, out) {             \
    int total=0;                    \
    for (int i=0; i<= max; i++){    \
        total += i;                 \
    }                               \
    out = total;                    \
}

int main(){
    int out, i=5;
    int total = 5;
    sum(5, out);
    printf("out= %i, original total=%i, i = %i\n", out, total,i);
}
