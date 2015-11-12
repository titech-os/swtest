C_SRCS = swtest.c
ASM_SRCS = swtch.S
OBJS = $(C_SRCS:%.c=%.o) $(ASM_SRCS:%.S=%.o)
EXES = swtest

CC = clang
CPPFLAGS =
CFLAGS = -std=c99 -Wall -Werror -g -m32 -mstackrealign
LD_FLAGS =
RM = rm -f

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

%.o: %.S
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

swtest: $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

.PHONY: all clean allclean

all: $(EXES)

clean:
	$(RM) $(EXES)
	$(RM) $(OBJS)

allclean: clean
	$(RM) *.o a.out
	$(RM) -r *.dSYM
	$(RM) *~
