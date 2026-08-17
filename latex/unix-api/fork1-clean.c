#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
int main(int argc, char *argv[]) {
    pid_t pid = getpid();
    printf("Parent pid: %d\n", (int) pid);
    pid_t child_pid = fork();
    if (child_pid > 0) {
        /* Parent Process */
        pid_t mypid = getpid();
        printf("[%d] parent of [%d]\n", (int) mypid, (int) cpid);
    } else if (child_pid == 0) { /* Child Process */
        mypid = getpid();
        printf("[%d] child\n", (int) mypid);
    } else {
        perror("Fork failed");
    }
    return 0;
}
