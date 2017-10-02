# swtest
# Simple examples for understanding the usage of xv6 swtch
# Copyright (C) 2017 Takuo Watanabe

LIB_SRCS = context.c
ASM_SRCS = swtch.S
EXE_SRCS = swtest.c schtest.c
LIB_OBJS = $(LIB_SRCS:%.c=%.o) $(ASM_SRCS:%.S=%.o)
ALL_OBJS = $(EXE_SRCS:%.c=%.o) $(LIB_OBJS)
EXES = swtest schtest

CC = clang
CPPFLAGS =
CFLAGS = -std=c99 -pedantic -Wall -Wextra -Werror -g -m32 -mstackrealign
LDFLAGS =
RM = rm -f

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

%.o: %.S
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

.PHONY: all clean allclean

all: $(EXES)

swtest: $(LIB_OBJS) swtest.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

schtest: $(LIB_OBJS) schtest.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

clean:
	$(RM) $(EXES)
	$(RM) $(ALL_OBJS)

allclean: clean
	$(RM) *.o a.out
	$(RM) -r *.dSYM
	$(RM) *~
