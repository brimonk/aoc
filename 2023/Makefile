CFLAGS=-Wall -g3 -I../
LDLIBS=-lm
SRCS=$(wildcard *.c)
BINS=$(SRCS:%.c=%)

all: $(BINS)

%: %.c
	$(CC) $(CFLAGS) -o $@ $< $(LDLIBS)

clean:
	rm $(BINS)
