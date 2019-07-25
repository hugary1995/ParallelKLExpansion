# CXX = g++
CXXFLAGS = -Wall -g -I include -I /usr/include/yaml-cpp -I eigen
MPICC?=mpicc

src = $(wildcard src/*.C)
obj = $(src:.C=.o)

KLExpansion: $(obj)
	$(MPICC) -lyaml-cpp -lstdc++ -lm -o $@ $^

.PHONY: clean

clean:
	rm -f src/*.o
