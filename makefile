test: test_set.cpp set.h set.cpp
	make clean
	g++ -o test test_set.cpp
	./test

clean:
	rm -f test