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
        TAILQ_ENTRY(twoint) twointp;
} twoint_td;

/* 
Not strictly required, but I typedef the list head type also. 
*/
typedef TAILQ_HEAD(listhead, twoint) head_td;

int main(int argc, char * argv[]){

    /*
    I'm heap allocating this, but I could just as easily stack allocated it
    if I'm passing it to lower contexts.
    */
    head_td *head = malloc(sizeof(head_td));

    TAILQ_INIT(head); //Setup the head pointers

    /* 
    Here I create a new item. I used the Insert head macro to patch up
    all the pointers withing the body
    */
    twoint_td *n1 = malloc(sizeof(twoint_td)); 
    n1->a = 1;
    n1->b = 1;
    TAILQ_INSERT_TAIL(head, n1, twointp);

    /*
    made a second item and added it to the list
    */
    twoint_td *n2 = malloc(sizeof(twoint_td));
    n2->a = 2;
    n2->b = 2;
    TAILQ_INSERT_TAIL(head, n2, twointp);

    /*
    dummy pointer for interation, initlized to first element of list
    */
    twoint_td *np = head->tqh_first;

    for(;np != NULL; np = np->twointp.tqe_next){ // list iteration
        printf("a:%d\n",np->a);
        printf("b:%d\n",np->b);
    }

    /*
    Get a pointer to the first eement, remove it from the list and free 
    the memory. Valgrind should show one less leak
    */
    np = head->tqh_first;
    printf("First is now\n");
    printf("a:%d\n",np->a);
    printf("b:%d\n",np->b);
    TAILQ_REMOVE(head, head->tqh_first, twointp);
//   free(np);

    np = head->tqh_first;
    printf("First is now\n");
    printf("a:%d\n",np->a);
    printf("b:%d\n",np->b);
    TAILQ_REMOVE(head, head->tqh_first, twointp);


    printf("Done\n");
}
