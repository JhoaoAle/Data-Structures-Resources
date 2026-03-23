#include <stdio.h>
#include <string.h>

int main(){
    int a[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
    char *b[15];
    for (int i = 0; i<15;i++){
        if(a[i]%3 == 0 && a[i]%5 == 0) {b[i] = "fizzbuzz";}
        else if(a[i]%3 == 0) {b[i] = "fizz";}
        else if(a[i]%5 == 0) {b[i] = "buzz";}
        else{sprintf(b[i], "%d", a[i]);}
        printf("%s \n", b[i]);
    }
    return 0;
}