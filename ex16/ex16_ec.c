#include<stdio.h>
#include<assert.h>
#include<stdlib.h>
#include<string.h>

//declare a persontype
struct Person {
    char *name;
    int age;
    int height;
    int weight;
};

//Builds persons with the requsite info, returns a pointer to the Person type
struct Person Person_create(char *name, int age, int height, int weight)
{
    //Get some memory that is the size of a person struct
    struct Person who;

    //set the respective fields
    who.name = strdup(name);
    who.age = age;
    who.height = height;
    who.weight = weight;

    //send back pointer to the newly prepared memory.
    return who;
}

void Person_print(struct Person who)
{
    //Generic outputter, expect person format.
    printf("Name: %s\n",who.name);
    printf("\tAge: %d\n",who.age);
    printf("\tHeight: %d\n",who.height);
    printf("\tWeight: %d\n",who.weight);
}

int main (int argc, char * argv[])
{

    //Make two people
    struct Person joe = Person_create(
            "Joe Alex", 32, 64, 140);

    struct Person frank = Person_create(
            "Frank Blank", 20,72,180);

    //print them out and where the are in memory
    printf("Joe is at memory location %p:\n", &joe);
    Person_print(joe);

    printf("Frank is at memory location %p:\n", &frank);
    Person_print(frank);

    //Make everyone age 20 years and print them again
    joe.age +=20;
    joe.height -=2;
    joe.weight += 40;
    Person_print(joe);

    frank.age +=20;
    frank.weight +=20;
    Person_print(frank);

    return 0;
}
