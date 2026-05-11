#include <stdint.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>

#define MAX_MEMO 96

// Memoization cache
long long memo[MAX_MEMO];

typedef struct {
    uint64_t a, b, c, d;
} Matrix;

Matrix multiply(Matrix x, Matrix y) {
    Matrix r;
    r.a = x.a * y.a + x.b * y.c;
    r.b = x.a * y.b + x.b * y.d;
    r.c = x.c * y.a + x.d * y.c;
    r.d = x.c * y.b + x.d * y.d;
    return r;
}

Matrix matrix_power(Matrix base, uint64_t n) {
    Matrix result = {1, 0, 0, 1}; // identity matrix

    while (n > 0) {
        if (n & 1)
            result = multiply(result, base);
        base = multiply(base, base);
        n >>= 1;
    }
    return result;
}

uint64_t fibonacci_matrix(uint64_t n) {
    if (n == 0) return 0;
    if (n == 1) return 1;

    Matrix fib = {1, 1, 1, 0};
    Matrix r = matrix_power(fib, n - 1);
    return r.a; // F(n)
}

void init_memo(void) {
    for (int i = 0; i < MAX_MEMO; i++)
        memo[i] = -1;
}

long long fibonacci_recursive(int n){
    if (n==0) return 0;
    if (n==1) return 1;
    else
        return fibonacci_recursive(n-1) + fibonacci_recursive(n-2);
}

long long fibonacci_memoization(int n){
    if (n == 0) return 0;
    if (n == 1) return 1;
    if (memo[n] != -1) return memo[n];
    memo[n] = fibonacci_memoization(n - 1) + fibonacci_memoization(n - 2);
    return memo[n];
}

long long fibonacci_binet_formula(int n){
    double sqrt5 = sqrt(5.0);
    double phi = (1.0 + sqrt5) / 2.0;
    double tau = (1.0 - sqrt5) / 2.0;
    double result = (pow(phi, n) - pow(tau, n)) / sqrt5;
    return (long long)(result + 0);
}

unsigned long long fibonacci_recurrent(int n){
    if (n == 0) return 0;
    if (n == 1) return 1;
    unsigned long long a = 0, b = 1;
    for (int i = 2; i <= n; i++) {
        unsigned long long temp = a + b;
        a = b;
        b = temp;
    }
    return b;
}

int input();

int main(){
    init_memo();
    int choice, n;
    uint64_t m;
    FILE *fp = fopen("input_fibonacci.txt", "r");

    while(1){
        printf("\n Main Menu \n");
        printf("1. Recursive Fibonacci\n");
        printf("2. Memoization Based Approach\n");
        printf("3. Formula based approach\n");
        printf("4. Recurrent approach\n");
        printf("5. Matrix-power based approach\n");
        printf("0. Exit\n\n");

        choice = input();
        switch(choice){
            case 0: return 0;

            case 1: {
                rewind(fp);
                printf("\n Calculating nth Fibonacci using recursion \n");
                while (fscanf(fp, "%d", &n) == 1 && (n > 0)) {
                    printf("%lld \n", fibonacci_recursive(n));
                }
                break;
            }
            case 2: {
                rewind(fp);
                printf("\n Calculating nth Fibonacci using Memoization \n");
                while (fscanf(fp, "%d", &n) == 1 && (n > 0)) {
                    printf("%lld \n", fibonacci_memoization(n));
                }
                break;
            }
            case 3: {
                rewind(fp);
                printf("\n Calculating nth Fibonacci using Binet's Formula \n");
                while (fscanf(fp, "%d", &n) == 1 && (n > 0)) {
                    printf("%lld \n", fibonacci_binet_formula(n));
                }
                break;
            }
            case 4: {
                rewind(fp);
                printf("\n Calculating nth Fibonacci using a Recurrent Approach \n");
                while (fscanf(fp, "%d", &n) == 1 && (n > 0)) {
                    printf("%llu \n", fibonacci_recurrent(n));
                }
                break;
            }
            case 5: {
                rewind(fp);
                printf("\n Calculating nth Fibonacci using a Matrix-Powers based Approach \n");
                while (fscanf(fp, "%llu", &m) == 1 && (m > 0)) {
                    printf("%llu \n", fibonacci_recurrent(m));
                }
                break;
            }
            default:
                printf("wrong Input\n");
        }
    }
}

int input()
{
    int number;
    scanf("%d", &number);
    return (number);
}