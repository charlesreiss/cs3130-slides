void *malloc(size_t size) {
    ...
    to_return = next_to_return;
    /* SIGNAL HAPPENS HERE */
    next_to_return += size;
    return to_return;
}

void foo() {
    /* This malloc() call interrupted */
    char *p = malloc(1024);
    @1p[0] = 'x'@;
}

void handle_sigint() {
    // printf might use malloc()
    printf("You pressed control-C.\n");
}
