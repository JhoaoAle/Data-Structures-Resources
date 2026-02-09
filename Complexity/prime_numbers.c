#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int is_prime(int n){
    for (int i=2; i<=n; i++) {
        if (n % i == 0) return 1;
        else return 0;
    }
}

int main(){
    int n;
    FILE *fp = fopen("input_primes.txt", "r");
    while (fscanf(fp, "%d", &n) == 1 && (n > 0)) {
        printf(" %s", is_prime(n) ? "true" : "false");
    }
    return 0;
}