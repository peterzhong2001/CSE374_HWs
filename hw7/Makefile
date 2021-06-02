# Peter Zhong
# CSE 374 HW7
# 06/06/2021

# Makefile for fraction number calculator

CPP = g++
CPPFLAGS = -Wall -std=c++11

# Compiling to executable named rcalc
rcalc: Calc.o Parser.o Fraction.o Scanner.o
	$(CPP) $(CPPFLAGS) -o rcalc Calc.o Parser.o Fraction.o Scanner.o

# making individual source files for all the cpp files written
Fraction.o: Fraction.cpp Fraction.h
	$(CPP) $(CPPFLAGS) -c Fraction.cpp

Scanner.o: Scanner.cpp Scanner.h
	$(CPP) $(CPPFLAGS) -c Scanner.cpp

Parser.o: Parser.cpp Parser.h Fraction.h Scanner.h Token.h
	$(CPP) $(CPPFLAGS) -c Parser.cpp

Calc.o: Calc.cpp Parser.h Fraction.h Scanner.h
	$(CPP) $(CPPFLAGS) -c Calc.cpp

debug: CPPFLAGS += -g
debug: rcalc

# clean up the working directory by removing everything except for source code
clean:
	rm -f *.o rcalc *~
