#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

/** Our old friend die from ex17. */
void die(const char *message)
{
    if (errno){
        perror(message);
    } else {
        printf("ERROR: %s\n",message);
    }

    exit(1);
}

// a typedef create a fake type in this case
// for a function pointer

// Notice: how compare_cb is the only token that is not a keyword.
// The usual "type" renamin format is typedef int foo
// this creates a type named foo, but that usage is dumb. 
// Besides nameing function pointers you can also name structs

typedef int (*compare_cb)(int a, int b);

/**
 * A classic buble sort function that uses the
 * the compare_cb to do the sorting
 */

//Return type is a int array. 
int *bubble_sort(int *numbers, int count, compare_cb cmp)
{
    int temp = 0;
    int i = 0;
    int j = 0;

    // This is where I stored the sorted copy
    //This is not an inplace sort, the sorted array is returned as a pointer.
    int *target = malloc(count * sizeof(int)); 
    if(!target) die("Memmory error.");

    //memcpy takes 3 arguments, a destination poitner, a source pointer, and 
    //the length in bytes to be copied. 
    memcpy(target,numbers,count * sizeof(int));

    //all the sort manipulations are done on the copy. 
    for(i =0; i < count; i++){
       for(j = 0; j < count - 1; j++) { //Two for loops means it's O(N^2)
           if(cmp(target[j], target[j+1]) > 0){
                //There is not explict dereference syntax for the function
                //pointer. Apparently under the hood, it's all function
                //pointers.
               temp = target[j+1];
               target[j+1] = target[j];
               target[j] = temp;
           }
       }
    }

    return target;
}

int sorted_order(int a, int b) //This functions "signature" matches that of compare cb
{
    return a - b;
}

int reverse_order(int a, int b)
{
    return b -a;
}

int strange_order(int a, int b)
{
    if(a == 0 || b == 0){
        return 0;
    } else {
        return a % b;
    }
}

/**
 * Used to test that we are sorting things correctly
 * by doing the sort and printing it out.
 */

void test_sorting(int *numbers, int count, compare_cb cmp)
{
    int i =0;
    int *sorted = bubble_sort(numbers, count, cmp); //passing around the function pointer

    if(!sorted) die("Failed to sort as request."); //This should probably never happen

    for (i=0; i < count; i++) {
        printf("%d ", sorted[i]);
    }

    printf("\n");

    free(sorted);

	/*
    unsigned char *data = (unsigned char * ) cmp;
    for (i = 0; i < 25; i++){
        printf("%02x:", data[i]);
    }

    printf("\n");
	*/
}

int main(int argc, char *argv[])
{
    if(argc < 2) die("USAGE: ex18 4 3 1 5 6");

    int count = argc -1;
    int i = 0;
    char **inputs = argv + 1; 

    // argv is an array of pointers, this makes argv a ** (pointer to pointer 
    // to char) incrementing argv, moves the argv pointer by one pointer size
    // (8 bytes in our case). Here we assign inputs to argv + 1 since
    // the executable name is always the first argument. When we use the
    // subscript operator on inputs, we're inidexing into the argv array of
    // pointers


    int *numbers = malloc(count * sizeof(int));
    if(!numbers) die("Memory error.");

    for(i = 0; i < count; i++){
        numbers[i] = atoi(inputs[i]);
    }

    //test_sorting(numbers, count, NULL);
    test_sorting(numbers, count, sorted_order);
    test_sorting(numbers, count, reverse_order);
    test_sorting(numbers, count, strange_order);

    free(numbers);

    return 0;

}
