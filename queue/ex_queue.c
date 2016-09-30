#include<stdio.h>
#include<stdlib.h>
#include<sys/queue.h>

/*
This is the data typedef. It has to be named for the macro to work but you
can later refer to it using the def'ed name
*/
typedef struct twoint {
        int a;
        int b;
        LIST_ENTRY(twoint) twointp;
} twoint_td;

/* 
Not strictly required, but I typedef the list head type also. 
*/
typedef LIST_HEAD(listhead, twoint) head_td;

int main(int argc, char * argv[]){

    head_td *head = malloc(sizeof(head_td)); //create a local copy of the list head

    LIST_INIT(head); //Setup the head pointers

    /* 
    Here I create a new item. I used the Insert head macro to patch up
    all the pointers withing the body
    */
    twoint_td *n1 = malloc(sizeof(twoint_td)); 
    n1->a = 1;
    n1->b = 1;
    LIST_INSERT_HEAD(head, n1, twointp);

    /*
    made a second item and added it to the list
    */
    twoint_td *n2 = malloc(sizeof(twoint_td));
    n2->a = 2;
    n2->b = 2;
    LIST_INSERT_HEAD(head, n2, twointp);

    /*
    dummy pointer for interation, initlized to first element of list
    */
    twoint_td *np = head->lh_first;

    for(;np != NULL; np = np->twointp.le_next){ // list iteration
        printf("a:%d\n",np->a);
        printf("b:%d\n",np->b);
    }

    /*
    Get a pointer to the first element, remove it from the list and free 
    the memory. Valgrind should show one less leak
    */
    np = head->lh_first;
    LIST_REMOVE(head->lh_first, twointp);
    free(np);

    np = head->lh_first;

    for(;np != NULL; np = np->twointp.le_next){
        printf("a:%d\n",np->a);
        printf("b:%d\n",np->b);
    }


    np = head->lh_first;
    LIST_REMOVE(head->lh_first, twointp);
    free(np);

    np = head->lh_first;
    printf("List should be empty now\n");
    for(;np != NULL; np = np->twointp.le_next){
        printf("a:%d\n",np->a);
        printf("b:%d\n",np->b);
    }

    free(head);

    printf("Done\n");
}
