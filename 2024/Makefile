LDLIBS=-lm
CFLAGS=-Wall -g3 -I../
SRCS=$(wildcard *.c)
BINS=$(SRCS:%.c=%)

all: $(BINS)

%: %.c
	$(CC) $(CFLAGS) -o $@ $< $(LDLIBS)

clean:
	rm $(BINS)
