/*
 * swtest
 * Simple examples for understanding the usage of xv6 swtch
 * Copyright (C) 2017 Takuo Watanabe
 */

#include <stdio.h>
#include <stdlib.h>

#include "context.h"
#include "swtch.h"

struct context *sch_ctx, *foo_ctx, *bar_ctx, *baz_ctx;

void foo(uint c) {
    while (1) {
        printf("foo : %d\n", c);
        c += 1;
        swtch(&foo_ctx, sch_ctx);
    }
}

void bar(uint c) {
    while (1) {
        printf("bar : %d\n", c);
        swtch(&bar_ctx, sch_ctx);
        c += 2;
    }
}

void baz(uint c) {
    while (1) {
        printf("baz : %d\n", c);
        swtch(&baz_ctx, sch_ctx);
        c += 3;
        printf("baz : %d\n", c);
        swtch(&baz_ctx, sch_ctx);
        c += 3;
    }
}

void scheduler() {
    while (1) {
        swtch(&sch_ctx, foo_ctx);
        swtch(&sch_ctx, bar_ctx);
        swtch(&sch_ctx, baz_ctx);
    }
}

int main() {
    uint *foo_stack = valloc(STACK_SIZE);
    uint *bar_stack = valloc(STACK_SIZE);
    uint *baz_stack = valloc(STACK_SIZE);
    foo_ctx = new_context(foo_stack + STACK_DEPTH, foo, 0);;
    bar_ctx = new_context(bar_stack + STACK_DEPTH, bar, 0);
    baz_ctx = new_context(baz_stack + STACK_DEPTH, baz, 0);
    scheduler();
    return 0;
}
