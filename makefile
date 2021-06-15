all: simulate

simulate: airport_simulate.o airport_simulate_main.o
	gcc -Wall -o simulate airport_simulate_main.o airport_simulate.o
	
airport_simulate_main.o: airport_simulate_main.c
	gcc -c -Wall airport_simulate_main.c
	
airport_simulate.o: airport_simulate.c
	gcc -c -Wall airport_simulate.c
	
clean:
	rm airport_simulate_main.o
	rm airport_simulate.o