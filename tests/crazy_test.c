#include<common.h>
#include<stdio.h>
#define IDENTITY(i, j) ((i == j) ? 1 : 0)
#define UPTRIANGLE(i, j) ((i <= j) ? 1 : 0)
#define DOWNTRIANGLE(i, j) ((i >= j) ? 1 : 0)
#define min(X, Y)  (X < Y) ? (X) : (Y)

int main(int argc, char * argv[]){
    matrix_t A=matones(3,1);
    matrix_t B=matgetcol(A,0);
    matmultscalar(B,3);
    matsetcol(A,B,0);
    matprint(A);

    int i,j;
    printf("IDENTITY:\n");
    for(i=0; i<5; i++){
        for(j=0; j<5; j++)
            printf("%d\t", IDENTITY(i, j));
        printf("\n");
    }
    printf("UPTRIANGLE:\n");
    for(i=0; i<5; i++){
        for(j=0; j<5; j++)
            printf("%d\t", UPTRIANGLE(i, j));
        printf("\n");
    }
    printf("DOWNTRIANGLE:\n");
    for(i=0; i<5; i++){
        for(j=0; j<5; j++)
            printf("%d\t", DOWNTRIANGLE(i, j));
        printf("\n");
    }
    matfree(&B);
    matfree(&A);
    return 0;
}
