#include <stdio.h>

int main(int argc, char *argv[])
{
    if (argc != 2){
        printf("Error: You need one argument.\n");
        //this is how you abort a program
        return 1;
    }

    int i = 0;
    for (i = 0; argv[1][i] != '\0'; i++){
        char letter = argv[1][i];
//        char letter;
//
        if (letter == 'a' || letter == 'A'){
            printf("%d: 'A'\n",i);

        } else if (letter == 'e' || letter == 'E') {
            printf("%d: 'E'\n",i);

        } else if (letter == 'i' || letter == 'I') {
            printf("%d: 'I'\n",i);

        } else if (letter == 'o' || letter == 'O') {
            printf("%d: 'O'\n",i);

        } else if (letter == 'u' || letter == 'U') {
            printf("%d: 'U'\n",i);

        } else if (letter == 'y' || letter == 'Y') {
            if(i > 2)  {
                // it's only sometimes Y
                printf("%d: 'Y'\n",i);
            } else{
               printf("%d: %c is not a vowel\n", i, letter);

            }
        } else {
            printf("%d: %c is not a vowel\n", i, letter);
        };

    /*
        switch(letter) {
            case 'a':
            case 'A':
                printf("%d: 'A'\n",i);
                break;

            case 'e':
            case 'E':
                printf("%d: 'E'\n",i);
                break;

            case 'i':
            case 'I':
                printf("%d: 'I'\n",i);
                break;

            case 'o':
            case 'O':
                printf("%d: 'O'\n",i);
                break;

            case 'u':
            case 'U':
                printf("%d: 'U'\n",i);
                break;

            case 'y':
            case 'Y':
                if(i > 2)  {
                    // it's only sometimes Y
                    printf("%d: 'Y'\n",i);
                    break;
                }

            default:
               printf("%d: %c is not a vowel\n", i, letter);
       }
    */
    }

    return 0;
}
