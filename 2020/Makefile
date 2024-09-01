SRCS=$(wildcard *.c)
PRGS=$(patsubst %.c,%,$(SRCS))
CFLAGS=-Wall -g3

all: $(PRGS)

%: %.c
	$(CC) $(CFLAGS) -o $@ $<

clean: 
	rm -f $(PRGS)
