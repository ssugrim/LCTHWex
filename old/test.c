#include <stdio.h>


int const * count_up(){
    static int i = 0;
    i++;
    return &i;
}

int main(){
    int *view = count_up();
    printf("Vaue %i \n", *view);
    count_up();
    printf("Vaue %i \n", *view);
    count_up();
    printf("Vaue %i \n", *view);
    *view = 1000;
    printf("Vaue %i \n", *view);
}
#include <stdio.h>
