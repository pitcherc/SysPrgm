#ifndef QUEUE_H_
#define QUEUE_H_

typedef struct customer {
	int arrivalTime;
	int proccessTime;
} customer;
int front;
int next;
void push(customer queue[], int arrival, int process);
int isEmpty(customer queue[]);
customer pop(customer queue[]);

#endif
