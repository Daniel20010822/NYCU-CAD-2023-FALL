CC = g++
FLAGS = -fdiagnostics-color=always -g -Wall -std=c++11

all: main

main: 312510158.cpp header.h
	$(CC) $(FLAGS) -o 312510158 312510158.cpp

hid:
	time ./312510158 hidden_1.v hidden_1.pat test_lib_hidden.lib
	diff 312510158_hidden_1_load.txt hidden/golden_hidden_1_load.txt
	diff 312510158_hidden_1_gate_info.txt hidden/golden_hidden_1_gate_info.txt
	diff 312510158_hidden_1_gate_power.txt hidden/golden_hidden_1_gate_power.txt
	diff 312510158_hidden_1_coverage.txt hidden/golden_hidden_1_coverage.txt

clean:
	rm -rf *.o
	rm -rf 312510158
	
clean_out:
	rm -rf 312510158_*_load.txt
	rm -rf 312510158_*_gate_info.txt
	rm -rf 312510158_*_gate_power.txt
	rm -rf 312510158_*_coverage.txt