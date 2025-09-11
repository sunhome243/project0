test: test_set.cpp set.h set.cpp
	g++ -o test test_set.cpp

clean:
	rm -f test