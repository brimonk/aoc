SRCS=$(wildcard *.c)
PRGS=$(patsubst %.c,%,$(SRCS))
CFLAGS=-Wall -g3 -I../

all: $(PRGS)

%: %.c
	$(CC) $(CFLAGS) -o $@ $<

clean: 
	rm -f $(PRGS)
