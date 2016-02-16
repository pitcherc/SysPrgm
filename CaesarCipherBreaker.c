#import <stdio.h>
#import <stdlib.h>

#define ALPH 26
#define SIZE 1024

char letterFreqFile[] = "LetFreq.txt";
char readFile[] = "InputText.txt";
float letFreq[ALPH] = {0}, inputFreq[ALPH]= {0};

void readFreq (float given[], char fname[]) {
	FILE *ifp = fopen(fname, "r");
	
	if (ifp == NULL) {
		fprintf(stderr, "Can't open input file LetFreq.txt\n");
		exit(1);
	}
	
	char *letter;
	float freq;
	int i=0;
	while (fscanf(ifp, "%c %f\n", letter, &freq) != EOF) {
		letFreq[i++] = freq;
	}
	
}

void calcFreq (float found[], char fname[]) {
	FILE *ifp = fopen(fname, "r");
	
	if (ifp == NULL) {
		fprintf(stderr, "Can't open input file InputText.txt\n");
		exit(1);
	}
	
	int i=0, c, count=0;
	while ((c = fgetc(ifp)) != EOF) {
		if (c >= (int)'A' && c <= (int)'Z'){
			found[(char)c - (int)'A']++;
			count++;
		} else if (c >= (int)'a' && c <= (int)'z') {
			found[(char)c - (int)'a']++;
			count++;
		}
	}
	
	for (int i=0; i < ALPH; i++){
		found[i] = found[i] / count;
	}
}

char rotate (char ch, int num) {
	if (ch >= (int)'A' && ch <= (int)'Z') {
		return (char)((((int)ch - (int)'A') + ALPH) - num) % ALPH + (int)'A';
	} else if (ch >= (int)'a' && ch <= (int)'z') {
		return (char)((((int)ch - (int)'a') + ALPH) - num) % ALPH + (int)'a';
	} else {
		return 0;
	}
}

int findKey (float given[], float found[]) {
	
	int i, j;
	float diff[ALPH] = {0};
	
	for (i=0; i < ALPH; i++) {
		for (j=0; j < ALPH; j++) {
			if(given[j] > found[(j+i) % ALPH])
				diff[i] = diff[i] + (given[j] - found[(j+i)%ALPH]);
			else
				diff[i] = diff[i] + (found[(j+i)%ALPH] - given[j]);
		}
	}
	
	float lowest = diff[0];
	int key = 0;
	for (i=1; i < ALPH; i++) {
		if (diff[i] < lowest) {
			lowest = diff[i];
			key = i;
		}
	}
	printf("%d\n",key);
	
	return key;
}

void decrypt (int key, char fname[]) {
	FILE *ifp = fopen(fname, "r");
	
	if (ifp == NULL) {
		fprintf(stderr, "Can't open input file InputText.txt\n");
		exit(1);
	}
	
	int c;
	while ((c = fgetc(ifp)) != EOF) {
		if (c >= (int)'A' && c <= (int)'Z'){
			printf("%c", rotate(c, key));
		} else if (c >= (int)'a' && c <= (int)'z') {
			printf("%c", rotate(c, key));
		} else {
			printf ("%c", c);
		}
	}
}

int main () {
	readFreq (letFreq, letterFreqFile);
	calcFreq (inputFreq, readFile);
	decrypt(findKey (letFreq, inputFreq), readFile);
	return 0;
}