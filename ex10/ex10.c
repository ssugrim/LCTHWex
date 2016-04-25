#include <stdio.h>

int main(int argc, char* argv[])
{
    int i = 0;

    //go through each string in argv
    //Why am I skipping argv[0]?


    //lets make our own array of strings
    char *states[] = {
        "California", "Oregon",
        "Washington", "Texas"
    };
    int num_states = 4;

    argv[1] = states[2];

    argc++;

    for(i=1; i<argc; i++){
        printf("arg %d: %s\n", i, argv[i]);
    }

    for (i  = 0; i < num_states; i++){
        printf("state %d: %s\n", i, states[i]);
    }

    return 0;
}
