#include <stdio.h>
#include <immintrin.h>

int main(int argc, char **argv) {
    volatile int array1[1024];
    for (int i = 0; i < 1024; ++i) {
        array1[i] = 0;
    }

    volatile int array2[32768];
    for (int i = 0; i < 32768; ++i) {
        array2[i] = 0;
    }

    array1[100] = 4;

    for (int i; i < 1024; i += 16) {
        long start = __builtin_ia32_rdtsc();
        array1[i];
        long end = __builtin_ia32_rdtsc();
        if (end - start < 50) {
            printf("%d %ld\n", i, end-start);
        }
    }
}

