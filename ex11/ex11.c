#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

    //go through each string in argv

    char **states = calloc(argc,sizeof(char*));
    int i = argc;



    while(i > 0) {
        i--;
        states[i] = argv[i];
    }

    i = argc;
    while (i > 0) {
        i--;
        printf("state %d: %s\n", i, states[i]);
    }

/*
    //lets make our own array of strings
    char *states[] = {
        "Liquid","Solid",
        "Gas", "Plasma"
    };

    int num_states = 4;

    i = num_states;

    while (i > -1) {
        i--;
        printf("state %d: %s\n", i, states[i]);
    }
*/

//    i = argc;
 //   while (i > 0){
  //      free(states[i]);
   // }
    free(states);
    return 0;
}
