all: Lab2 Ni

Lab2: Lab2_files/Lab2.o
	g++ Lab2_files/Lab2.o -o Lab2

Lab2.o: Lab2_files/Lab2.cpp

Ni: Ni_files/main.o Ni_files/Logger.o
	g++ Ni_files/main.o Ni_files/Logger.o -o Ni

main.o: Ni_files/main.cpp
	g++ -c Ni_files/main.cpp

Logger.o: Ni_files/Logger.cpp Ni_files/Logger.h
	g++ -c Ni_files/Logger.cpp

clean:
	rm Lab2_files/*.o Ni_files/*.o Ni Lab2
