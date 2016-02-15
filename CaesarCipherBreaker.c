#import <stdio.h>
#import <stdlib.h>

#define TOTAL 26

char letterFreqFile[] = "LetFreq.txt";
float letFreq[26];

void readFreq (float given[], char fname[]) {
	FILE *ifp;
	char *mode = "r";
	
	ifp = fopen(fname, mode);
	
	if (ifp == NULL) {
		fprintf(stderr, "Can't open input file LetFreq.txt\n");
		exit(1);
	}
	
	char letter[1];
	float freq;
	int i=0;
	while (fscanf(ifp, "%s %f", letter, &freq) != EOF) {
		letFreq[i++] = freq;
	}
	
	fclose(ifp);
}

void calcFreq (float found[], char fname[]) {
	
}

char rotate (char ch, int num) {
	return 0;
}

int findKey (float given[], float found[]) {
	return 0;
}

void decrypt (int key, char fname[]) {
	
}

int main () {
	readFreq(letFreq, letterFreqFile);
	return 0;
}