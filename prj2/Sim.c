#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "queue.h"

#define AVG_SERVICE 2.0
#define SIZE 1500

int expdist (double mean) {
	double r = rand();
	r /= RAND_MAX;
	return -mean * log(r);
}

int cashierOpen (int cashiers[], int numCashiers, int timeOfDay) {
	for(int i = 0; i < numCashiers; i++) {
		if(cashiers[i] < timeOfDay) {
			return i;
		}
	}
	return -1;
}

int main (int argc, char *argv[]) {
	int t, timeOfDay;
	int custPerMin[5], percent[5];
	int numCashiers = 7;
	customer queue[SIZE];
	
	if(argv[2] != NULL) {
		numCashiers = atoi(argv[2]);
	}
	int cashiers[numCashiers];
	
	FILE *fp;
	fp = fopen(argv[1], "r");
	if (fp == NULL) {
		fprintf(stderr, "Can't open input file %s\n", argv[1]);
		exit(1);
	}
	
	int i = 0;
	while(fscanf(fp, "%d %d\n", &custPerMin[i], &percent[i]) == 2) {
		i++;
	}
	fclose(fp);
	
	int lower0 = 1;
	int upper0 = percent[0];
	int lower1 = 1 + percent[0];
	int upper1 = percent[0] + percent[1];
	int lower2 = 1 + percent[0] + percent[1];
	int upper2 = percent[0] + percent[1] + percent[2];
	int lower3 = 1 + percent[0] + percent[1] + percent[2];
	int upper3 = percent[0] + percent[1] + percent[2] + percent[3];
	int lower4 = 1 + percent[0] + percent[1] + percent[2] + percent[3];
	int upper4 = percent[0] + percent[1] + percent[2] + percent[3] + percent[4];
	
	timeOfDay = 0;
	while(timeOfDay < 480 || !isEmpty(queue)) {
		
		//after hours
		if(!isEmpty(queue) && timeOfDay > 480) {
			int num = cashierOpen(cashiers, numCashiers, timeOfDay);
			if(num > -1) {
				while(!isEmpty(queue) && cashierOpen(cashiers, numCashiers, timeOfDay) != -1) {
					customer first = pop(queue);
					int open = cashierOpen(cashiers, numCashiers, timeOfDay);
					cashiers[num] = first.proccessTime;
				}
			}
			timeOfDay++;
			continue;
		}
		
		int r = (rand() % upper4) + 1;
		int customers = 0;
		
		if(r >= lower0 && r <= upper0) {
			customers = custPerMin[0];
		}
		if(r >= lower1 && r <= upper1) {
			customers = custPerMin[1];
		}
		if(r >= lower2 && r <= upper2) {
			customers = custPerMin[2];
		}
		if(r >= lower3 && r <= upper3) {
			customers = custPerMin[3];
		}
		if(r >= lower4 && r <= upper4) {
			customers = custPerMin[4];
		}
		
		//if there is a line
		if(!isEmpty(queue)) {
			int num = cashierOpen(cashiers, numCashiers, timeOfDay);
			if(num != -1) {
				customer first = pop(queue);
			}
			for(int j = 0; j < customers; j++) {
				t = expdist (AVG_SERVICE);
				push(queue, timeOfDay, t);
			}
		} else {	//if there is no line
			for(int j = 0; j < customers; j++) {
				t = expdist (AVG_SERVICE);
				int num = cashierOpen(cashiers, numCashiers, timeOfDay);
				if(num != -1) {
					push(queue, timeOfDay, t);
				} else {
					cashiers[num] += t;
				}
			}
		}

		timeOfDay++;
	}
}
