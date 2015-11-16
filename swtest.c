#include <stdio.h>
#include <stdlib.h>

typedef unsigned int uint;

struct context {
    uint edi;
    uint esi;
    uint ebx;
    uint ebp;
    uint eip;
};

#define STACK_SIZE 4096
#define STACK_DEPTH (STACK_SIZE / sizeof(uint))

// swtch.S
void swtch(struct context **old, struct context *new);

#define push(s, v) (*--(s)=(v))

struct context *new_context(uint *sp, void (*fun)(uint), uint arg) {
    push(sp, arg);
    push(sp, 0);
    sp -= sizeof(struct context) / sizeof(uint);
    struct context *ctx = (struct context *)sp;
    ctx->eip = (uint)fun;
    return ctx;
}

struct context *foo_ctx, *bar_ctx, *main_ctx;

void foo(uint arg) {
    int c = arg;
    while (1) {
        printf("foo : %d\n", c);
        swtch(&foo_ctx, bar_ctx);
        c += 2;
    }
}

void bar(uint arg) {
    int c = arg;
    while (1) {
        printf("bar : %d\n", c);
        swtch(&bar_ctx, main_ctx);
        c += 3;
    }
}

int main() {
    uint *foo_stack = valloc(STACK_SIZE);
    uint *bar_stack = valloc(STACK_SIZE);
    foo_ctx = new_context(foo_stack + STACK_DEPTH, foo, 1);;
    bar_ctx = new_context(bar_stack + STACK_DEPTH, bar, 1);
    int c = 1;
    while (1) {
        printf("main: %d\n", c);
        swtch(&main_ctx, foo_ctx);
        c += 1;
    }
    return 0;
}

