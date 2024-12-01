CFLAGS=-Wall -Wuninitialized -g3 -I../
SRCS=$(wildcard *.c)
BINS=$(SRCS:%.c=%)

all: $(BINS)

%: %.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm $(BINS)
