# CXX = g++
CXXFLAGS = -Wall -g -I include -I /usr/include/python2.7
MPICC?=mpicc

src = $(wildcard src/*.C)
obj = $(src:.C=.o)

KLExpansion: $(obj)
	$(MPICC) -lpython2.7 -lstdc++ -lm -o $@ $^

.PHONY: clean

clean:
	rm -f src/*.o
