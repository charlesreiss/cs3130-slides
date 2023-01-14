void @3handle_sigint@(int signum) {
    write(1, "Control-C pressed?!\n",
        sizeof("Control-C pressed?!\n"));
}

int main(void) {
    struct sigaction act;
    act.sa_handler = @3&handle_sigint@;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    @2sigaction(SIGINT, &act, NULL);@

    char buf[1024];
    while (fgets(buf, sizeof buf, stdin)) {
        printf("read %s", buf);
    }
}
