#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
int main(int argc, char *argv[]) {
    pid_t pid = @2getpid()2@;
    printf("Parent pid: %d\n", @3(int)3@ pid);
    pid_t child_pid = fork();
    if (child_pid > 0) {
        /* Parent Process */
        pid_t my_pid = @2getpid()2@;
        printf("[%d] parent of [%d]\n", @3(int)3@ my_pid, @3(int)3@ child_pid);
    } else if (child_pid == 0) {
        /* Child Process */
        pid_t my_pid = @2getpid()2@;
        printf("[%d] child\n", @3(int)3@ my_pid);
    } else {
        @4perror4@("Fork failed");
    }
    return 0;
}
