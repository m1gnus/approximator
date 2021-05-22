.PHONY: all clean
CC=gcc
CFLAGS=-Wall -pedantic -Wextra
LDFLAGS=

OBJS=main.o util.o
BIN=linear_approx

all: linear_approx

$(BIN): main.o util.o
	@echo ===== LINKING $@
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

%.o: %.c
	@echo ===== BUILDING $@
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@echo ===== CLEANING
	rm -f $(OBJS) $(BIN)
