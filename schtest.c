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

void foo(void *arg) {
    int c = (int)arg;
    while (1) {
        printf("foo : %d\n", c);
        swtch(&foo_ctx, sch_ctx);
        c += 1;
    }
}

void bar(void *arg) {
    int c = (int)arg;
    while (1) {
        printf("bar : %d\n", c);
        swtch(&bar_ctx, sch_ctx);
        c += 2;
    }
}

void baz(void *arg) {
    int c = (int)arg;
    while (1) {
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
    void **foo_stack = valloc(STACK_SIZE);
    void **bar_stack = valloc(STACK_SIZE);
    void **baz_stack = valloc(STACK_SIZE);
    foo_ctx = new_context(foo_stack + STACK_DEPTH, foo, (void *)0);
    bar_ctx = new_context(bar_stack + STACK_DEPTH, bar, (void *)0);
    baz_ctx = new_context(baz_stack + STACK_DEPTH, baz, (void *)0);
    scheduler();
    return 0;
}
