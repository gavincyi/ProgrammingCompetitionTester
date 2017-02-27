INCLUDES = -I.
LIBS = -lm
FLAGS = -std=c++1y -Wall -Wno-unused-function -O3 -o
COMPILER = g++

tests: TestBinarian TestCountBits

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