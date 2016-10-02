#include "dbg.h"
#include<stdio.h>
#include<stdlib.h>
#include <pthread.h>
#include <unistd.h>

typedef struct{
    int id;
    int count;
    int *p;
} arg_t;

void * worker (void * func_arg){
    check(func_arg != NULL,"Bad arg");
    int limit = ((arg_t *) func_arg)->count;
    int id = ((arg_t *) func_arg)->id;
    int *flag = ((arg_t *) func_arg)->p;
    int i = 0;

    for (i=0; i < limit; i++){
        debug("Thread %d at %d",id,i);
        sleep(0.25);
    }
    *flag = 1;

    return NULL;

error:
    debug("Error");
    return NULL;
}


void * watcher (void * func_arg){
    check(func_arg != NULL,"Bad arg");
    int id = ((arg_t *) func_arg)->id;
    int *flag = ((arg_t *) func_arg)->p;
    int i = 0;

    while(1){
        if (*flag == 1){
            debug("Thread %d at %d",id,i);
            return NULL;
        }
        else{
            i++;
        }
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
    int *flag = malloc(sizeof(int));
    *flag = 0;

    arg_1->id = 1;
    arg_1->count = 100;
    arg_1->p = flag;

    arg_2->id = 2;
    arg_2->count = 10;
    arg_2->p = flag;

    int result_code = 0;
    result_code = pthread_create(&t_1, NULL, worker, arg_1);
    check(result_code == 0, "problem creating thread 1");
    pthread_create(&t_2, NULL, watcher, arg_2);
    check(result_code == 0, "problem creating thread 2");

    pthread_join(t_2, NULL);

    return 0;

error:
    return 1;
}
