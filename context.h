/*
 * swtest
 * Simple examples for understanding the usage of xv6 swtch
 * Copyright (C) 2017 Takuo Watanabe
 */

typedef unsigned int uint;

// x86 (i386) context (taken from xv6/proc.h)
struct context {
    uint edi;
    uint esi;
    uint ebx;
    uint ebp;
    uint eip;
};

#define STACK_SIZE 4096
#define STACK_DEPTH (STACK_SIZE / sizeof(uint))

struct context *new_context(uint *, void (*)(int), int);
