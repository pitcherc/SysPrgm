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
	return (char)(((int)ch - num) % ALPH);
}

int findKey (float given[], float found[]) {
	return 0;
}

void decrypt (int key, char fname[]) {
	
}

int main () {
	readFreq (letFreq, letterFreqFile);
	printf ("%f\n", letFreq[1]);
	calcFreq (inputFreq, readFile);
	printf ("%f\n", inputFreq[1]);
	return 0;
}