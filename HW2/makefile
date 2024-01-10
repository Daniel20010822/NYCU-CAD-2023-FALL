CC = g++
FLAGS = -fdiagnostics-color=always -g -Wall -std=c++11

all: main

main: 312510158.cpp header.h
	$(CC) $(FLAGS) -o 312510158 312510158.cpp

c17: clean_out
	time -p ./312510158 c17.v -l test_lib.lib

example: clean_out
	time -p ./312510158 example.v -l test_lib.lib

c432: clean_out
	time -p ./312510158 c432.v -l test_lib.lib

c54321: clean_out
	time -p ./312510158 c54321.v -l test_lib.lib


clean:
	rm -rf *.o
	rm -rf 312510158

clean_out:
	rm -rf 312510158_*_delay.txt
	rm -rf 312510158_*_path.txt
	rm -rf 312510158_*_load.txt
