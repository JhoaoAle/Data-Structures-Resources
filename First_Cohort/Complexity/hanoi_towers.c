#include<stdio.h>

void hanoi_solver(int n, char origin_rod, char destination_rod, char auxiliary_rod){
    if (n==1){
        printf("\n Move disk %d from rod %c to rod %c", n, origin_rod, destination_rod);
        return;
    }
    hanoi_solver(n-1, origin_rod, auxiliary_rod, destination_rod);
    printf("\n Move disk %d from rod %c to rod %c", n, origin_rod, destination_rod);
    hanoi_solver(n-1, auxiliary_rod, destination_rod, origin_rod);
}

int main(){
    int n = 50;
    hanoi_solver(n, 'A', 'C', 'B');
    return 0;
}