#include <stdio.h>
#include <stdlib.h>

void build(int *arr, int start, int end, int *idx) {
    if (start > end) return;

    int mid = (start + end) / 2;

    // place root
    arr[*idx] = mid;
    (*idx)++;

    // left subtree
    build(arr, start, mid - 1, idx);

    // right subtree
    build(arr, mid + 1, end, idx);
}

int main() {
    int n;
    scanf("%d", &n);

    if (n <= 0) {
        printf("Invalid n\n");
        return 0;
    }

    int arr[n];
    int idx = 0;

    build(arr, 1, n, &idx);

    // print result
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i != n - 1) printf(" ");
    }
    printf("\n");

    return 0;
}