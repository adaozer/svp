all: svp.o finish.o pre_process.o vector_functions.o main.cpp
		g++ -o runme main.cpp finish.o svp.o pre_process.o vector_functions.o

finish.o: finish.cpp finish.h
		g++ -c finish.cpp

svp.o: svp.cpp svp.h
		g++ -c svp.cpp
		
pre_process.o: pre_process.cpp pre_process.h
		g++ -c pre_process.cpp

vector_functions.o: vector_functions.cpp vector_functions.h
		g++ -c vector_functions.cpp

clean:
		rm -rf runme result.txt finish.o svp.o pre_process.o vector_functions.o

test:	
		@make all
		@./runme [1.0 2.0] [2.0 2.0]
		@if [ "`cat result.txt`" = "1" ]; then \
	    	echo "Test passed"; \
		else \
	    	echo "Test failed"; \
		fi
		@make clean
	