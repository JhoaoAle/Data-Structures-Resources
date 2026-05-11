#include <stdio.h>
#include <stdbool.h>

bool is_prime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;

    for (int i = 5; (long)i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    }
    return true;
}

int main(void) {
    int n = 700;                      
    int current = 1000000007;
    bool want_prime = true;

    FILE *out = fopen("input_numbers.txt", "w");
    if (!out) {
        perror("Failed to open file");
        return 1;
    }

    for (int count = 0; count < n; count++) {
        while (is_prime(current) != want_prime) {
            current++;
        }

        fprintf(out, "%d\n", current);

        want_prime = !want_prime;
        current++;
    }

    fprintf(out, "0\n");

    fclose(out);
    return 0;
}
