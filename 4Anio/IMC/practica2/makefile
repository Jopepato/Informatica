CXXFLAGS += -Wall -Wextra -O3 -std=c++17
DEBUG += -g

all: practica2

clean:
	rm -rf *.o practica2

PerceptronMulticapa.o: PerceptronMulticapa.cpp PerceptronMulticapa.h
	$(CXX) $(CXXFLAGS) -c PerceptronMulticapa.cpp

practica1: PerceptronMulticapa.o practica1.hpp practica2.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@
	rm -rf *.o
