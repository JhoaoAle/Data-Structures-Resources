#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool is_prime(int n){
    if (n <= 1) return false;
    for (int i=2; i < n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

int main(){
    int n;
    FILE *fp = fopen("input_numbers.txt", "r");
    if(!fp){
        perror("File not found");
        return 1;
    }
    while (fscanf(fp, "%d", &n) == 1 && (n > 0)) {
        printf(" %s \n", is_prime(n) ? "true" : "false");
    }
    fclose(fp);
    return 0;
}