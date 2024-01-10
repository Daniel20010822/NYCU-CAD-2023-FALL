CC = g++
FLAGS = -fdiagnostics-color=always -g -Wall -std=c++11

all: main

main: 312510158.cpp header.h
	$(CC) $(FLAGS) -o 312510158 312510158.cpp

c17: clean_out
	time -p ./312510158 c17.v -l test_lib.lib
	diff 312510158_c17_load.txt golden/golden_c17_load.txt
	diff 312510158_c17_delay.txt golden/golden_c17_delay.txt
	diff 312510158_c17_path.txt golden/golden_c17_path_2.txt
example: clean_out
	time -p ./312510158 example.v -l test_lib.lib
	diff 312510158_example_load.txt golden/golden_example_load.txt
	diff 312510158_example_delay.txt golden/golden_example_delay.txt
	diff 312510158_example_path.txt golden/golden_example_path.txt
c432: clean_out
	time -p ./312510158 c432.v -l test_lib.lib
	diff 312510158_c432_delay.txt golden/golden_c432_delay.txt
	diff 312510158_c432_path.txt golden/golden_c432_path.txt
	diff 312510158_c432_load.txt golden/golden_c432_load.txt
c54321: clean_out
	time -p ./312510158 c54321.v -l test_lib.lib
	diff 312510158_c54321_path.txt golden/golden_c54321_path.txt
	# diff 312510158_c54321_load.txt golden/golden_c54321_load.txt
	# diff 312510158_c54321_delay.txt golden/golden_c54321_delay.txt

compare: clean_out
	./312510158 c17.v -l test_lib.lib
	diff 312510158_c17_load.txt orig_out/312510158_c17_load.txt
	diff 312510158_c17_delay.txt orig_out/312510158_c17_delay.txt
	diff 312510158_c17_path.txt orig_out/312510158_c17_path.txt

	./312510158 example.v -l test_lib.lib
	diff 312510158_example_load.txt orig_out/312510158_example_load.txt
	diff 312510158_example_delay.txt orig_out/312510158_example_delay.txt
	diff 312510158_example_path.txt orig_out/312510158_example_path.txt

	./312510158 c432.v -l test_lib.lib
	diff 312510158_c432_load.txt orig_out/312510158_c432_load.txt
	diff 312510158_c432_delay.txt orig_out/312510158_c432_delay.txt
	diff 312510158_c432_path.txt orig_out/312510158_c432_path.txt

	./312510158 c54321.v -l test_lib.lib
	diff 312510158_c54321_load.txt orig_out/312510158_c54321_load.txt
	diff 312510158_c54321_delay.txt orig_out/312510158_c54321_delay.txt
	diff 312510158_c54321_path.txt orig_out/312510158_c54321_path.txt

compare_ze: clean_out
	./312510158 c17.v -l test_lib.lib
	diff 312510158_c17_load.txt ze_out/312510152_c17_load.txt
	diff 312510158_c17_delay.txt ze_out/312510152_c17_delay.txt
	# diff 312510158_c17_path.txt ze_out/312510152_c17_path.txt

	./312510158 example.v -l test_lib.lib
	diff 312510158_example_load.txt ze_out/312510152_example_load.txt
	diff 312510158_example_delay.txt ze_out/312510152_example_delay.txt
	diff 312510158_example_path.txt ze_out/312510152_example_path.txt

	./312510158 c54321.v -l test_lib.lib
	diff 312510158_c54321_load.txt ze_out/312510152_c54321_load.txt
	diff 312510158_c54321_delay.txt ze_out/312510152_c54321_delay.txt
	diff 312510158_c54321_path.txt ze_out/312510152_c54321_path.txt

clean:
	rm -rf *.o
	rm -rf 312510158

clean_out:
	rm -rf 312510158_*_delay.txt
	rm -rf 312510158_*_path.txt
	rm -rf 312510158_*_load.txt