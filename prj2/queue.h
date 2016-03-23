#ifndef QUEUE_H_
#define QUEUE_H_

typedef struct customer {
	int arrivalTime;
	int proccessTime;
} customer;
void push(customer queue[], int arrival, int process);
customer pop(customer queue[]);

#endif
