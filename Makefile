all: svp.o pre_process.o vector_functions.o main.cpp
		g++ -o runme main.cpp pre_process.o vector_functions.o

svp.o: svp.cpp svp.h
		g++ -c svp.cpp

pre_process.o: pre_process.cpp pre_process.h
		g++ -c pre_process.cpp

vector_functions.o: vector_functions.cpp vector_functions.h
		g++ -c vector_functions.cpp