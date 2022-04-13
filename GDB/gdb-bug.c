/*
 * Sample C Program For GDB Tutorial
 * By Xinru Yang
 * 2015-5-10
 *
 * Problem: Big Integer Square Root (WITH BUG)
 * Algorithm: O(N^2)
 *   Guess answer 0~9 for every digit, from high to low.
 *   Compare input and squared answer.
 */

#include <stdio.h>
#include <string.h>

#define N 1000

/* Set zero to a big integer */
void big_zero(int *a) {
    memset(a, 0, N * sizeof(int));
}

/* Big integer a = b */
void big_copy(int *a, int *b) {
    memcpy(a, b, N * sizeof(int));
}

/* Converts an input string to a big integer. */
void big_read(int *a) {
    char buff[N];
    scanf("%s", &buff); /* <-- 1 */
    int n = (int) strlen(buff);
    big_zero(a);
    
    for (int i = 0; i < n; ++i) {
        a[n - i - 1] = buff[i];  /* <-- 2 */
    }
}

/* Outputs an big integer */
void big_print(int *a) {
    int first = 1;
    for (int i = N - 1; i >= 0; --i) {
        if (first != 1 || a[i] != 0) {
            printf("%d", a[i]);
            first = 0;
        }
    }

    if (first == 1) {
        printf("0\n");
    } else {
        printf("\n");
    }
}

/* Compares two big integer, returns Sign(a-b) */
int big_compare(int *a, int *b) {
    for (int i = N - 1; i >= 0; --i) {
        if (a[i] < b[i]) return -1;
        if (a[i] > b[i]) return 1;
        if (a[i] == b[i]) return 0; /* <-- 3 */
    }
    return 0;
}

/* Addition a = a + b */
void big_add(int *a, int *b) {
    int carry = 0;
    for (int i = 0; i < N; ++i) {
        a[i] += b[i] + carry;
        carry = a[i] / 10;
        a[i] = a[i] % 10;
    }
}

/* Decimal shift a = a * 10^k */
void big_shift(int *a, int k) {
    for (int i = N - 1; i >= k; ++i) {  /* <-- 4 */
        a[i] = a[i - k];
    }
    for (int i = k - 1; i >= 0; --i) {
        a[i] = 0;
    }
}

/* Floor of big integer's square root a = sqrt(a)*/
void big_sqrt(int *a) {
    int root[N], sqr[N];
    big_zero(root);
    
    int t[N], last_t[N];
    big_zero(t);

    for (int i = (N - 1) / 2; i >= 0; --i) {
        for (int j = 1; j <= 9; ++j) {
            big_copy(last_t, t);

            /* (r+1)^2 = r^2 + (r) + (r+1) */
            big_add(t, root);
            ++root[i];
            big_add(t, root);

            /* (r * 10^i)^2 = (r^2 * 10^i) * 10^i */
            big_copy(sqr, t);
            big_shift(sqr, i);

            if (big_compare(a, sqr) < 0) {
                --root[i];
                big_copy(t, last_t);
                break;
            }
        }
        
        /* (r^2 * 10^i) = (r^2 * 10^(i-1)) * 10 */
        big_shift(t, 1);
    }

    big_copy(a, root);
}

int main(void) {
    int a[N];
    big_read(a);
    big_sqrt(a);
    big_print(a);
    return 0;
}
