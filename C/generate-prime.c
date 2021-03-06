#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "isPrime.h"
#include "common.h"

LongNumber generatePrime(int n);
double getNanoTime();
LongNumber fromArrayToInt(char* array, int n);

int main(int argc, char** argv){
	if(argc < 2) { 
			printf("Usage generate-prime <bit number>\n");
			return 0;
	}
	int bits = atoi(argv[1]);

	printf("\n");
	printf("#######################################################\n");
	printf("# PRIME NUMBER GENERATOR                              #\n");
	printf("#######################################################\n");
	printf("# This tool will generate a prime number of %3d bits  #\n", bits);
	printf("# In this machine the size of LongNumber is %3d bytes #\n", sizeof(LongNumber));
	printf("#                                                     #\n");
	unsigned long prime = generatePrime(bits);
	printf("# The prime number is %lu\n", prime);
	printf("#######################################################\n");
	printf("\n");
}

LongNumber generatePrime(int n){
	char* rand_number_array = (char*)malloc(n*sizeof(char));
	unsigned long prime_test;
	do {
		// Generate the random number of n bits
		// ex. [1,1,0,0,0,0,0,1] = 1100001
		int i = 0;
		for(i = 0; i < n; i++){
			// Last number is always 1
			if(i == n - 1) { rand_number_array[i] = 1; break; }
			srand(getNanoTime());
			rand_number_array[i] = rand() % 2;
			//printf("number %d\n", rand_number_array[i]);
		}
		prime_test = fromArrayToInt(rand_number_array, n);
	} while(!isPrime(prime_test));
	return prime_test; 
}

LongNumber fromArrayToInt(char* array, int n){
	unsigned long number = 0;
	int i = 0;
	for(i = n - 1; i >= 0; i--){
		if(array[i] == 0) continue;
		number += pow(2, n - i - 1);  
	}
	return number;
}

double getNanoTime(){
	struct timespec ts;
	timespec_get(&ts, 1);
	//char buff[100];
	//strftime(buff, sizeof buff, "%D %T", gmtime(&ts.tv_sec));
	//printf("Current time: %s.%09ld UTC\n", buff, ts.tv_nsec);
	return ts.tv_nsec;
}
