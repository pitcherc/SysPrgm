#include "queue.h"
#include <stdio.h>

void push(customer queue[], int arrival, int process) {
	customer c = {arrival, process};
	queue[next] = c;
	next++;
}

int isEmpty(customer queue[]) {
	if(next == front) {
		next = front = 0;
		return 1;
	}
	return 0;
}

customer pop(customer queue[]) {
//	if(front == next){
//		customer c = {0,0};
//		return c;
//	}
	customer c = queue[front];
	front++;
	return c;
}
