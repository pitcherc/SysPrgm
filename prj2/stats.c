#include "stats.h"
#include <stdio.h>

void calc(int waitTime, int count, int time) {
	printf("Number of Customers: %d\n", count);
	printf("Average Wait Time: %f\n", (double) waitTime/count);
	printf("Closing Time: %d\n", time);
}
