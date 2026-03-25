# include <stdio.h>
# include <math.h>
# include <stdlib.h>

int main(){

    unsigned long long int n, i, triangular, k, kplus1;
    // Reading inputs from file
    FILE *fp = fopen("input_triangular_numbers.txt", "r");

    if (fp == NULL){
        printf("Unable to open file \n");
        return 0;
    }
    else {
        // First approach. Naive
        /*
        //while(scanf("%llu", &n) && (n > 0)){
        while (fscanf(fp, "%llu", &n) == 1 && (n > 0)) {
            triangular = 0;
            for (i = 1; triangular < n; i++){
                triangular += i;
            }
            if (triangular == n)
                printf("YES\n");
            else
                printf("NO\n");
        }   
        */

        // Second approach. Based on Gauss Formula
        while (fscanf(fp, "%llu", &n) == 1 && (n > 0)) {
            k = (-1 + sqrt(1 + 8 * n)) / 2;
            kplus1 = k + 1;
            triangular = (k * kplus1 ) / 2;
            if( triangular == n)
            printf ("YES\n");
            else
            printf ("NO\n");
        }
        // Thsi gives different results, explain why.
    }
    return 0;
}

