#include<stdio.h>

int main(int argc, char * argv[])
{
/*
    int areas[] = {10, 12, 13, 14, 20};

    areas[2000] = 9;

    printf("The first area is %d, and the 2nd is %d.\n",
            areas[2000],areas[1]);
*/
    
  char name[] = "Zed";
    char full_name[] = {
        'Z','e','d',
        ' ', 'A', '.' ,' ',
        'S', 'h', 'a', 'w','\0'
    };

    full_name[2] = name[0];


//    name[2] = 'a';

    //WARNING: On some systems you may have to change the 
    //%ld in this code to a %u since it will use unsinged ints
    //
/*
    printf("The size of an int: %ld\n",sizeof(int));
    printf("the size of areas (int[]): %ld\n",
            sizeof(areas));
    printf("The first area is %d, and the 2nd is %d.\n",
            areas[0],areas[1]);

    printf("The size of a char: %ld\n",sizeof(char));
    printf("The size of name (char[]): %ld\n",
            sizeof(name));
    printf("The number of chars: %ld\n",
            sizeof(name) / sizeof(char));

    printf("The size of full_name (char[]): %ld\n",
            sizeof(full_name));
    printf("The number of chars: %ld\n",
            sizeof(full_name) / sizeof(char));
*/

    printf("name=\"%s\" and full_name=\"%s\"\n",
            name, full_name);
    return 0;
}
