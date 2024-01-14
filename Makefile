all: file_write.o svp.o pre_process.o vector_functions.o main.cpp
		g++ -o runme main.cpp file_write.o svp.o pre_process.o vector_functions.o

file_write.o: file_write.cpp file_write.h
		g++ -c file_write.cpp

svp.o: svp.cpp svp.h
		g++ -c svp.cpp
		
pre_process.o: pre_process.cpp pre_process.h
		g++ -c pre_process.cpp

vector_functions.o: vector_functions.cpp vector_functions.h
		g++ -c vector_functions.cpp

clean:
		rm -rf runme result.txt file_write.o svp.o pre_process.o vector_functions.o