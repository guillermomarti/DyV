all: tests_unitarios tests_oraculo tiempos

tiempos: tiempos.cpp dyv.o
	g++ -std=c++11 -Wall tiempos.cpp dyv.o -o tiempos

tests_unitarios: tests_unitarios.cpp dyv.o
	g++ -std=c++11 -Wall tests_unitarios.cpp dyv.o -o tests_unitarios

tests_oraculo: tests_oraculo.cpp dyv.o
	g++ -std=c++11 -Wall tests_oraculo.cpp dyv.o -o tests_oraculo

dyv.o: dyv.cpp dyv.h
	g++ -std=c++11 -Wall -c dyv.cpp

clean:
	rm -f *.o tests_unitarios tests_oraculo tiempos *.pdf *.csv