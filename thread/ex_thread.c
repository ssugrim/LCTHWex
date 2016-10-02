#include "dbg.h"
#include<stdio.h>
#include<stdlib.h>
#include <pthread.h>
#include <unistd.h>

typedef struct{
    int id;
    int count;
} arg_t;

void * worker (void * func_arg){
    check(func_arg != NULL,"Bad arg");
    int limit = ((arg_t *) func_arg)->count;
    int id = ((arg_t *) func_arg)->id;
    int i = 0;

    for (i=0; i < limit; i++){
        debug("Thread %d at %d",id,limit);
        sleep(1);
    }

    return NULL;

error:
    debug("Error");
    return NULL;
}

int main(int argc, char * argv[]){

    pthread_t t_1,t_2;
    arg_t *arg_1, *arg_2;

    arg_1 = malloc(sizeof(arg_t));
    arg_2 = malloc(sizeof(arg_t));
    arg_1->id = 1;
    arg_1->count = 100;

    arg_2->id = 2;
    arg_2->count = 10;

    pthread_create(&t_1, NULL, worker, arg_1);
    pthread_create(&t_2, NULL, worker, arg_2);

    pthread_join(t_1, NULL);
    pthread_join(t_2, NULL);

    return 0;
}
