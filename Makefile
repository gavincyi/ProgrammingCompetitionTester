INCLUDES = -I.
LIBS = -lm -lrt
FLAGS = -std=c++11 -Wall -Wno-unused-function -O3 -o
COMPILER = g++

test: TestBinarian TestCountBits TestLatency

TestBinarian:
	rm -f TestBinarian
	$(COMPILER) $(FLAGS) TestBinarian test/TestBinarian.cpp $(LIBS) $(INCLUDES)
	./TestBinarian
	rm TestBinarian
	
TestCountBits:
	rm -f TestCountBits
	$(COMPILER) $(FLAGS) TestCountBits test/TestCountBits.cpp $(LIBS) $(INCLUDES)
	./TestCountBits
	rm TestCountBits
	
TestLatency:
	rm -f TestLatency
	$(COMPILER) $(FLAGS) TestLatency test/TestLatency.cpp $(LIBS) $(INCLUDES)
	./TestLatency
	rm TestLatency	
