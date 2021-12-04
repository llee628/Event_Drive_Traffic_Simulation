all: proj5.exe

project5.o: project5.cpp SortedListClass.h SortedListClass.inl FIFOQueueClass.h FIFOQueueClass.inl LinkedNodeClass.h LinkedNodeClass.inl
	g++ -std=c++98 -g -Wall -c project5.cpp -o project5.o

proj5.exe: project5.o
	g++ -std=c++98 project5.o -o proj5.exe

clean:
	rm -f *.o *.exe