$CFLAGS = -std=c99 -Wall

all: pnmdump.exe

%.exe: %main.c
	gcc $(CFLAGS) $< -o $@

test: pnmdump.exe
	python tests/runtests-1.0.py ./pnmdump.exe