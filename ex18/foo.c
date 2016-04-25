#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char *argv[])
{
    int i = atoi(argv[1]);
    int j = (i + 1) / atoi(argv[2]);
    printf("j: %d\n",j);

    return 0;
}
