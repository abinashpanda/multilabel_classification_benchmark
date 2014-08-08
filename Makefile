CC=g++

CFLAGS=-Wall

all: benchmark

benchmark: benchmark.cpp
	$(CC) benchmark.cpp -lshogun -o benchmark

clean:
	rm -f benchmark
	rm -f massif*
