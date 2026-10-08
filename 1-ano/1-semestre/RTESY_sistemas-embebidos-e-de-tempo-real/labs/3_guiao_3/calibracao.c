#include <stdio.h>
#include <time.h>

int main(void) {
    const long N = 10000000;
    volatile double x = 0.0;

    struct timespec t0, t1;

    clock_gettime(CLOCK_MONOTONIC, &t0);

    for (long i = 0; i < N; i++) {
        x += i * 0.000001;
    }

    clock_gettime(CLOCK_MONOTONIC, &t1);

    double elapsed =
        (t1.tv_sec - t0.tv_sec) +
        (t1.tv_nsec - t0.tv_nsec) / 1e9;

    printf("N = %ld\n", N);
    printf("Elapsed = %.9f s\n", elapsed);
    printf("x = %f\n", x);

    return 0;
}
