project1: main.o RefMon.o object.o subject.o
	g++ -o project1 main.o RefMon.o object.o subject.o $(ARGS)

main.o: main.cpp
	g++ -c main.cpp

RefMon.o: RefMon.cpp
	g++ -c RefMon.cpp

object.o: object.cpp
	g++ -c object.cpp
	
subject.o: subject.cpp
	g++ -c subject.cpp

clean:
	rm *.o project1
 