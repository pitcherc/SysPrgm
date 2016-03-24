#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include "queue.h"
#include "stats.h"

#define AVG_SERVICE 2.0
#define SIZE 3000

int custPerMin[5], percent[5];

double expdist (double mean) {
	double r = rand();
	r /= RAND_MAX;
	return -mean * log(r);
}

int cashierOpen (int cashiers[], int numCashiers, int timeOfDay) {
	for(int i = 0; i < numCashiers; i++) {
//		fprintf(stderr, "Cashier%d: %d\n", i, cashiers[i]);
		if(cashiers[i] <= timeOfDay) {
			return i;
		}
	}
	return -1;
}

void simulation(int numOfTellers) {
	int t, timeOfDay;
	int numCashiers = numOfTellers;
	customer queue[SIZE];
	int totalWait = 0, totalCustomers = 0;
	int cashiers[numCashiers];
	for(int i = 0; i < numCashiers; i++) {
		cashiers[i] = 0;
	}
//	fprintf(stderr, "Cashiers: %d %d\n", cashiers[0], cashiers[1]);
	
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
//		fprintf(stderr, "Time: %d\n", timeOfDay);
		int customers = 0;
		//after hours
		if(!isEmpty(queue) && timeOfDay >= 480) {
			int num = cashierOpen(cashiers, numCashiers, timeOfDay);
			if(num > -1) {
				while(!isEmpty(queue) && cashierOpen(cashiers, numCashiers, timeOfDay) != -1) {
					customer first = pop(queue);
					int open = cashierOpen(cashiers, numCashiers, timeOfDay);
					totalWait += timeOfDay - first.arrivalTime;
					cashiers[num] += first.proccessTime;
				}
			}
		} else {
			
			int r = (rand() % upper4) + 1;
			
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
//			fprintf(stderr, "Customers: %d\n", customers);
			totalCustomers += customers;
			
			//if there is a line
			if(!isEmpty(queue)) {
//				fprintf(stderr, "Line:\n");
				while(cashierOpen(cashiers, numCashiers, timeOfDay) != -1 && !isEmpty(queue)) {
					int line = cashierOpen(cashiers, numCashiers, timeOfDay);
					//fprintf(stderr, "here");
					customer first = pop(queue);
//					fprintf(stderr, "POP->Line ArivalTimeTime: %d\n", first.arrivalTime);
					totalWait += timeOfDay - first.arrivalTime;
					cashiers[line] += first.proccessTime;
				}
				int num = cashierOpen(cashiers, numCashiers, timeOfDay);
				if(num == -1){
				for(int j = 0; j < customers; j++) {
					t = (int)expdist (AVG_SERVICE)+1;
//					fprintf(stderr, "PUSH->Cust%d ProccessTime: %d %d\n", j, t, timeOfDay);
					push(queue, timeOfDay, t);
				}
				} else {
					for(int j = 0; j < customers; j++) {
						t = (int)expdist (AVG_SERVICE);
//						fprintf(stderr, "Cust%d ProccessTime: %d\n", j, t);
						int num = cashierOpen(cashiers, numCashiers, timeOfDay);
						cashiers[num] += t;
					}
				}
			} else {	//if there is no line
//				fprintf(stderr, "NoLn:\n");
				for(int j = 0; j < customers; j++) {
					t = (int)expdist (AVG_SERVICE)+1;
//					fprintf(stderr, "Cust%d ProccessTime: %d\n", j, t);
					int num = cashierOpen(cashiers, numCashiers, timeOfDay);
					if(num == -1) {
//						fprintf(stderr, "PUSH->Cust%d ProccessTime: %d %d\n", j, t, timeOfDay);
						push(queue, timeOfDay, t);
					} else {
						cashiers[num] += t;
					}
				}
			}
		}
		
		
//		fprintf(stderr, "TotalCustomers: %d\n", totalCustomers);
//		fprintf(stderr, "TotalWaitTime: %d\n\n", totalWait);
		//getchar();
		timeOfDay++;
	}
	calc(totalWait, totalCustomers, timeOfDay);
}

int main (int argc, char *argv[]) {
	
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
	
	simulation(4);
	simulation(5);
	simulation(6);
	simulation(7);
}
