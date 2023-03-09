#include <pthread.h>
#include <stdio.h>

int x, y;
extern void *thread_A(void*);
extern void *thread_B(void*);

void test() {
    x = y = 0;
    pthread_t A, B;
    pthread_create(&A, NULL, thread_A, NULL);
    pthread_create(&B, NULL, thread_B, NULL);
    void *A_result, *B_result;
    pthread_join(A, &A_result);
    pthread_join(B, &B_result);
    printf("A:%d B:%d\n", (int) A_result, (int) B_result);
}

int main(void) {
    for (int i = 0; i < 100000000; ++i) {
        test();
    }
}
