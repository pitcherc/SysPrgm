a.out:
	gcc -c stats.c
	gcc -c queue.c
	gcc -c Sim.c -std=c99
	gcc -o a.out -g stats.o queue.o Sim.o -lm
stats.o: stats.c
queue.o: queue.c
Sim.o: Sim.c

