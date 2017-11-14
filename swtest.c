/*
 * swtest
 * Simple examples for understanding the usage of xv6 swtch
 * Copyright (C) 2017 Takuo Watanabe
 */

#include <stdio.h>
#include <stdlib.h>

#include "context.h"
#include "swtch.h"

struct context *foo_ctx, *bar_ctx, *baz_ctx;

void foo(void *arg) {
    int c = (int)arg;
    while (1) {
        printf("foo : %d\n", c);
        swtch(&foo_ctx, bar_ctx);
        c += 1;
    }
}

void bar(void *arg) {
    int c = (int)arg;
    while (1) {
        printf("bar : %d\n", c);
        swtch(&bar_ctx, baz_ctx);
        c += 2;
    }
}

void baz(void *arg) {
    int c = (int)arg;
    while (1) {
        printf("baz : %d\n", c);
        swtch(&baz_ctx, foo_ctx);
        c += 3;
    }
}

int main() {
    void **bar_stack = valloc(STACK_SIZE);
    void **baz_stack = valloc(STACK_SIZE);
    bar_ctx = new_context(bar_stack + STACK_DEPTH, bar, (void *)0);
    baz_ctx = new_context(baz_stack + STACK_DEPTH, baz, (void *)0);
    foo(0);
    return 0;
}

