foo() {
  char *@2p@ = malloc(1024)... {
    to_return = @1next_to_return@;
    handle_sigint() { /* signal delivered here */
      printf("You pressed control-C.\n") {
        @1buf@ = malloc(...) {
          to_return = @1next_to_return@;
          next_to_return += size;
          return to_return;
        }
        ...
      }
    }
    next_to_return += size;
    return @2to_return@;
  }
  /* now p points to buf used by printf! */
}
