# CXX = g++
CXXFLAGS = -Wall -g -I include -I /usr/include/python2.7 -I /usr/include/yaml-cpp
MPICC?=mpicc

src = $(wildcard src/*.C)
obj = $(src:.C=.o)

KLExpansion: $(obj)
	$(MPICC) -lpython2.7 -lyaml-cpp -lstdc++ -lm -o $@ $^

.PHONY: clean

clean:
	rm -f src/*.o
