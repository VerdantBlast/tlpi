#include <stdio.h>
#include <setjmp.h>

static jmp_buf env;

void do_something(void)
{
    setjmp(env);
    printf("done");
}

int main()
{
    do_something();
    longjmp(env, 1);
}

// Segmentation fault