#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "queue.h"

#define AVG_SERVICE 2.0
#define SIZE 3000

double expdist (double mean) {
	double r = rand();
	r /= RAND_MAX;
	return -mean * log(r);
}

int main (int argc, char *argv[]) {
	double t, timeOfDay;
	int custPerMin[5], percent[5];
	int numCashiers = 7;
	
	if(argv[2] != NULL) {
		numCashiers = atoi(argv[2]);
	}
	double cashiers[numCashiers];
	
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
	while(timeOfDay < 480) {
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
		
		for(int j = 0; j < customers; j++) {
			t = expdist (AVG_SERVICE);
			for(int i = 0; i < numCashiers; i++) {
				if(cashiers[i] < timeOfDay) {
					cashiers[i] += t;
					break;
				}
			}
		}
		timeOfDay++;
	}
}
