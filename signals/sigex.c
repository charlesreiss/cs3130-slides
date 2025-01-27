void @3handle_sigint@(int signum) {
    /* signum == SIGINT */
    write(1, "Control-C press?!\n", sizeof("Control-C press?!\n"));
}

int main(void) {
    struct sigaction act;
    act.sa_handler = @3&handle_sigint@;
    sigemptyset(&act.sa_mask);
    // SA_RESTART = if syscall interrupted,
    // complete it when handler returns
    act.sa_flags = SA_RESTART;
    @2sigaction(SIGINT, &act, NULL);@

    char buf[1024];
    while (fgets(buf, sizeof buf, stdin)) {
        printf("read %s", buf);
    }
}
