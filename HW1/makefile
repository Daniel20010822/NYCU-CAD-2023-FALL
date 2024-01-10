CC = g++
FLAGS = -fdiagnostics-color=always -g -Wall -std=c++11

all:
	clear
	$(CC) $(FLAGS) -o 312510158.o 312510158.cpp


verify:
	./312510158.o demo/testcase/input1.txt output1.txt
	./312510158.o demo/testcase/input2.txt output2.txt
	./312510158.o demo/testcase/input3.txt output3.txt
	./312510158.o demo/testcase/input4.txt output4.txt
	./312510158.o demo/testcase/input5.txt output5.txt
	./312510158.o demo/testcase/input6.txt output6.txt
	./demo/verify -t demo/testcase/input1.txt -g demo/golden/output1.txt -s output1.txt
	./demo/verify -t demo/testcase/input2.txt -g demo/golden/output2.txt -s output2.txt
	./demo/verify -t demo/testcase/input3.txt -g demo/golden/output3.txt -s output3.txt
	./demo/verify -t demo/testcase/input4.txt -g demo/golden/output4.txt -s output4.txt
	./demo/verify -t demo/testcase/input5.txt -g demo/golden/output5.txt -s output5.txt
	./demo/verify -t demo/testcase/input6.txt -g demo/golden/output6.txt -s output6.txt
	./312510158.o testcase/input1.txt output1.txt
	./312510158.o testcase/input2.txt output2.txt
	./312510158.o testcase/input3.txt output3.txt
	./312510158.o testcase/input4.txt output4.txt
	./312510158.o testcase/input5.txt output5.txt
	./312510158.o testcase/input6.txt output6.txt
	diff output1.txt testcase/output1.txt
	diff output2.txt testcase/output2.txt
	diff output3.txt testcase/output3.txt
	diff output4.txt testcase/output4.txt
	diff output5.txt testcase/output5.txt
	diff output6.txt testcase/output6.txt

clean:
	rm -rf *.o
	rm -rf output*.txt
