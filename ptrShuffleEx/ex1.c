#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    unsigned char* foo = malloc(20);
    foo[0]='a';
    foo[1]='a';
    foo[2]='a';
    foo[3]='a';
    foo[4]='a';
    foo[5]='a';

    foo[6]='b';
    foo[7]='b';
    foo[8]='b';
    foo[9]='b';
    foo[10]='b';
    foo[11]='b';

    int i = 0;
    for(i = 0; i < 20; i++){
        printf ("%c",foo[i]);
    }
    printf("\n");

    unsigned char tmp_mac[6];
    unsigned char* src = foo;
    unsigned char* dst = foo + 6; //Equivalent to &foo[6]

    memcpy(tmp_mac, src, 6);
    memcpy(src, dst, 6);
    memcpy(dst, tmp_mac, 6);

    for(i = 0; i < 20; i++){
        printf ("%c",foo[i]);
    }
    printf("\n");
}
