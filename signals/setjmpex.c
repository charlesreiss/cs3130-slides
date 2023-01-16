#include <setjmp.h>
#include <stdio.h>
jmp_buf env;
int counter = 0;
void foo() {
    while (setjmp(env) == 1) {
        puts("A");
    }
    puts("B");
    bar();
}

void bar() {
    puts("C");
    ++counter;
    if (counter < 2) {
        longjmp(env, 1);
    }
}

int main() {
    foo();
}
