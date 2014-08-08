CC=g++

CFLAGS=-Wall

all: benchmark

benchmark: benchmark.cpp
	g++ benchmark.cpp -lshogun -o benchmark

clean:
	rm benchmark
	rm massif*
