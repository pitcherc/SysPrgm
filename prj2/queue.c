#import "queue.h"

void push(customer queue[], int arrival, int process) {
	customer c = {arrival, process};
	queue[next] = c;
	next++;
}

int isEmpty(customer queue[]) {
	if(next == 0) {
		return 1;
	}
	return 0;
}

customer pop(customer queue[]) {
	customer c = queue[front];
	front++;
	return c;
}