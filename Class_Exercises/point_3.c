#include <stdio.h>
#include <stdlib.h>

int compar(const void *a, const void *b) {
    long long aa = *(long long*)a;
    long long bb = *(long long*)b;
    if (aa < bb) return -1;
    if (aa > bb) return 1;
    return 0;
}

int binary_search(long long arr[], int n, long long key) {
    int left = 0, right = n - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (arr[mid] == key) return 1;
        if (arr[mid] < key) left = mid + 1;
        else right = mid - 1;
    }
    return 0;
}

int main() {
    int N;
    while (scanf("%d", &N) == 1) {
        int X[N];
        long long S = 0;
        for (int i = 0; i < N; i++) {
            scanf("%d", &X[i]);
            S += X[i];
        }
        
        if (S % 3 != 0) {
            printf("0\n");
            continue;
        }
        
        long long step = S / 3;
        
        // Construir posiciones acumuladas
        long long pos[N];
        pos[0] = 0;
        for (int i = 1; i < N; i++) {
            pos[i] = pos[i-1] + X[i-1];
        }
        
        qsort(pos, N, sizeof(long long), compar);
        
        int count = 0;
        for (int i = 0; i < N; i++) {
            long long target1 = (pos[i] + step) % S;
            long long target2 = (pos[i] + 2 * step) % S;
            
            // Buscar target1 y target2 en pos
            if (binary_search(pos, N, target1) && binary_search(pos, N, target2)) {
                count++;
            }
        }
        
        // Cada triángulo se cuenta 3 veces
        printf("%d\n", count / 3);
    }
    return 0;
}