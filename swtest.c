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

void foo(int c) {
    while (1) {
        printf("foo : %d\n", c);
        c += 1;
        swtch(&foo_ctx, bar_ctx);
    }
}

void bar(int c) {
    while (1) {
        printf("bar : %d\n", c);
        swtch(&bar_ctx, baz_ctx);
        c += 2;
    }
}

void baz(int c) {
    while (1) {
        printf("baz : %d\n", c);
        swtch(&baz_ctx, foo_ctx);
        c += 3;
        printf("baz : %d\n", c);
        swtch(&baz_ctx, foo_ctx);
        c += 3;
    }
}

int main() {
    uint *bar_stack = valloc(STACK_SIZE);
    uint *baz_stack = valloc(STACK_SIZE);
    bar_ctx = new_context(bar_stack + STACK_DEPTH, bar, 0);
    baz_ctx = new_context(baz_stack + STACK_DEPTH, baz, 0);
    foo(0);
    return 0;
}

