CXX ?= g++
CXXFLAGS ?= -std=c++17 -O2 -Wall -Wextra -Wpedantic

all: sha256sum_cpp test_sha256

sha256sum_cpp: main.cpp sha256.cpp sha256.hpp
	$(CXX) $(CXXFLAGS) -o $@ main.cpp sha256.cpp

test_sha256: test_sha256.cpp sha256.cpp sha256.hpp
	$(CXX) $(CXXFLAGS) -o $@ test_sha256.cpp sha256.cpp

test: test_sha256
	./test_sha256

clean:
	rm -f sha256sum_cpp test_sha256

.PHONY: all test clean
