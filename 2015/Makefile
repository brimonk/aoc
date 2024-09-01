SRCS=$(wildcard *.c)
PRGS=$(patsubst %.c,%,$(SRCS))
CFLAGS=-Wall -g3 -I../
LDLIBS=-lssl -lcrypto -lm

all: $(PRGS)

%: %.c
	$(CC) $(CFLAGS) -o $@ $< $(LDLIBS)

clean: 
	rm -f $(PRGS)
