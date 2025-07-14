#include <stdio.h>

int f(int x) {
    return x * x - x - 12;
}

int bisection_method(int n) {
    int a = 0, b = n - 1;

    while (a <= b) {
        int m = (a + b) / 2;
        int f_m = f(m);

        if (f_m == 0) {
            return m;
        } else if (f(a) * f_m < 0) {
            b = m - 1;
        } else {
            a = m + 1; 
        }
    }

    return -1;
}

int main() {
    int n = 8;
    int root = bisection_method(n);

    if (root != -1) {
        printf("Root: %d\n", root);
    } else {
        printf("No integer root found in the given range.\n");
    }

    return 0;
}
