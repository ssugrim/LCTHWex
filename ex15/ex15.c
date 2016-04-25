#include <stdio.h>

void print_arr(int* cur_age, char** cur_name,int count)
{
    int i = 0;
    for(i=count-1; i > -1; i--){
        printf("%s is %d years old.\n",
                *(cur_name+i), *(cur_age+i));
    }
}

void print_age(int* age_start, int* age_end)
{
    if(age_start > age_end)
    {
        printf("Error: Start greater than end\n");
        return;
    }

    long int count = age_end - age_start;
    printf("Length of age is: %ld\n",count);

    for (;age_end > age_start - 1;age_end--)
    {
        printf("Value of age_end: %d\n", *age_end);
    }

}

int main(int argc, char *argv[])
{
    //create two arrays we care about
    int ages[] = {23,43,12,89,2};
    char *names[] = {
        "Alan","Frank",
        "Mary","John","Lisa"
    };

    //safely get the size of ages
    int count = sizeof(ages) / sizeof(int);
    int i = 0;

    //first way using indexing
    for(i=0; i < count; i++){
        printf("%s has %d years alive.\n",
                names[i],ages[i]);
    }

    printf("---\n");

    // setup the pointer to the start of the arrays
    int *cur_age = ages;
    char **cur_name = names;

    //second way moved to function.
    print_arr(ages, names, count); 


    printf("---\n");

    //thirdway, pointers are just arrays
    for(i=0; i < count; i++){
        printf("%s has %d years old again.\n",
                cur_name[i],cur_age[i]);
    }

    printf("---\n");

    //fourth way with pointers in a stupid complex way
    for( cur_name = names + count - 1 , cur_age = ages + count - 1;
            (cur_age - ages) > -1;
            cur_name--, cur_age--)
    {
        printf("%s lived %d years so far.\n",
                *cur_name, *cur_age);
    }

    printf("---\n");


    //Printing out the addresses being used
    for (i = 0; i < count; i++)
    {
        printf("ages: %d is at %p \n", i, &ages[i]);
    }
    for (i = 0; i < count; i++)
    {
        printf("names: %d is at %p \n", i, &names[i]);
    }

    printf("---\n");

    printf("Sizeof char**: %lu\n",sizeof(char**));
    printf("Sizeof char*: %lu\n",sizeof(char*));
    printf("Sizeof int*: %lu\n",sizeof(int*));

    printf("---\n");

    print_age(ages, ages + count-1);
    return 0;
}

