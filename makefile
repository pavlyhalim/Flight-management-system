
output: main.o myList.o flightticket.o flighthashtable.o
	g++ main.o myList.o flightticket.o flighthashtable.o -o output

main.o: main.cpp
	g++ -c main.cpp

myList.o: myList.cpp myList.h
	g++ -c myList.cpp

flightticket.o: flightticket.cpp flightticket.h
	g++ -c flightticket.cpp

flighthashtable.o: flighthashtable.cpp flighthashtable.h
	g++ -c flighthashtable.cpp

clean:
	rm *.o output