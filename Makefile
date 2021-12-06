all: proj5.exe

CarClass.o: CarClass.cpp CarClass.h constants.h
	g++ -std=c++98 -g -Wall -c CarClass.cpp -o CarClass.o

EventClass.o: EventClass.cpp EventClass.h constants.h
	g++ -std=c++98 -g -Wall -c EventClass.cpp -o EventClass.o

IntersectionSimulationClass.o: IntersectionSimulationClass.cpp IntersectionSimulationClass.h SortedListClass.h SortedListClass.inl EventClass.h FIFOQueueClass.h FIFOQueueClass.inl CarClass.h random.h LinkedNodeClass.h LinkedNodeClass.inl
	g++ -std=c++98 -g -Wall -c IntersectionSimulationClass.cpp -o IntersectionSimulationClass.o

random.o: random.cpp random.h
	g++ -std=c++98 -g -Wall -c random.cpp -o random.o

project5.o: project5.cpp SortedListClass.h SortedListClass.inl FIFOQueueClass.h FIFOQueueClass.inl LinkedNodeClass.h LinkedNodeClass.inl IntersectionSimulationClass.h EventClass.h CarClass.h
	g++ -std=c++98 -g -Wall -c project5.cpp -o project5.o

proj5.exe: project5.o CarClass.o EventClass.o IntersectionSimulationClass.o random.o
	g++ -std=c++98 project5.o CarClass.o EventClass.o IntersectionSimulationClass.o random.o -o proj5.exe

clean:
	rm -f *.o *.exe