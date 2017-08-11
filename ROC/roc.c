#include<stdio.h>

typedef struct{
    float FP;
    float TP;
} r_type;

int main(int argc, char *argv[])
{

    int i = 0;
    float scores[10] = {0.9,0.8,0.7,0.6,0.55,0.54,0.53,0.52,0.51,0.505};
    int labels[10] = {1,1,0,1,1,1,0,0,1,0}; // p = 1, n = 0;
    r_type R[10];

    for(i = 0; i < 10; i++){
        R[i].FP = 0;
        R[i].TP = 0;
    }

    float P = 6;
    float N = 4;
    int FP = 0;
    int TP = 0;

    printf("values:\n");
    for(i = 0; i < 10; i++){
        if(labels[i] == 1){
            TP += 1;
        }
        else{
            FP += 1;
        }
        R[i].FP = FP / N;
        R[i].TP = TP / P;

        if (labels[i] == 1){
            printf("%2d, p %f, FP: %f, TP %f, FP count %d, TP count %d \n",
            (i+1),scores[i],R[i].FP, R[i].TP, FP,TP);
        } else{
            printf("%2d, n %f, FP: %f, TP %f, FP count %d, TP count %d \n",
            (i+1),scores[i],R[i].FP, R[i].TP, FP,TP);
        }
    }
    return 0;
}
