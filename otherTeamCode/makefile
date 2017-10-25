test : test.o
	g++ -std=c++11 test.o -L. libAPI.so -o test

test.o : test.cpp
	g++ -std=c++11 -c test.cpp

clean:
	rm *.o
