a.out:	main.o Simulation.o Student.o 
	g++ main.o Simulation.o Student.o

main.o:	main.cpp Simulation.h
	g++ -c main.cpp

Simulation.o: Simulation.cpp Simulation.h DoublyLinkedList.h Queue.h Student.h
	g++ -c Simulation.cpp

Student.o: Student.cpp Student.h
	g++ -c Student.cpp

clean:
	rm -f *.o a.out

run:
	./a.out
