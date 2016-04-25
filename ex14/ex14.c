#include <stdio.h>
#include <ctype.h>
#include <string.h>

// forward declarations
//int can_print_it(char ch);
void print_letters(int len, char arg[]);

void print_arguments(int argc, char *argv[])
{
    int i =0;

    for (i = 0; i < argc; i++){
        
        print_letters(strlen(argv[i]),argv[i]);
    }
}

void print_letters(int len, char arg[])
{
    int i = 0;
    printf("Length of arg was: %d\n",len);

   // for (i=0; arg[i] != '\0'; i++){
    for (i=0; i < len; i++){
        char ch = arg[i];

        //if (can_print_it(ch)){
        if (isalpha(ch) || isblank(ch)){
            printf("'%c' == %d ", ch, ch);
        };
    }

    printf("\n");
}

/*
int can_print_it(char ch)
{
    return isalpha(ch) || isblank(ch);

}
*/

int main(int argc, char * argv[])
{
    print_arguments(argc,argv);
    return 0;
}

