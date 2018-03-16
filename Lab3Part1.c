#include <stdio.h>

int main(void) {
	int inputValue;
	const int oneQuarter = 25, oneDime = 10, oneNickel = 5;
	
	//Initial user prompt
	printf("Please give an amount in cents less than 100: ");
	scanf(" %d",&inputValue);
	
	//Loop for user to continue entering, if invalid amount, program ends
	while(inputValue > 0 && inputValue < 100){
		int numQuarters = 0, numDimes = 0, numNickels = 0, numCents = 0;
		
		printf("%d cents: ",inputValue);
		
		//this loop is for quarters, counts number of quarters and then has
		//if statements printing different cases
		for( ; inputValue >= oneQuarter; numQuarters ++) {
			inputValue = inputValue - oneQuarter;
		}
		
		if(numQuarters == 1) {
			if(inputValue == 0) {
				printf("%d quarter.", numQuarters);
			} else {
				printf("%d quarter, ", numQuarters);
			}
		} else if(numQuarters > 1) {
			if(inputValue == 0) {
				printf("%d quarters.", numQuarters);
			} else {
				printf("%d quarters, ", numQuarters);
			}
		}
		
		//similar structure to previous but for dimes
		for( ; inputValue >= oneDime; numDimes ++) {
			inputValue = inputValue - oneDime;
		}
		
		if(numDimes == 1) {
			if(inputValue == 0) {
				printf("%d dime.", numDimes);
			} else {
				printf("%d dime, ", numDimes);
			}
		} else if(numDimes > 1) {
			if(inputValue == 0) {
				printf("%d dimes.", numDimes);
			} else {
				printf("%d dimes, ", numDimes);
			}
		}
		
		//same again, for nickels
		for( ; inputValue >= oneNickel; numNickels ++) {
			inputValue = inputValue - oneNickel;
		}
		
		if(numNickels == 1) {
			if(inputValue == 0) {
				printf("%d nickel.", numNickels);
			} else {
				printf("%d nickel, ", numNickels);
			}
		} else if(numNickels > 1) {
			if(inputValue == 0) {
				printf("%d nickels.", numNickels);
			} else {
				printf("%d nickels, ", numNickels);
			}
		}
		
		//slightly modified since one cent = 1
		numCents = inputValue;
		if(numCents == 1) {
			printf("%d cent.", numCents);
		} else if(numCents > 1) {
				printf("%d cents.", numCents);
		}
		
		//re-prompts user
		printf("\nPlease give an amount in cents less than 100: ");
		scanf(" %d",&inputValue);
	}
	
	printf("Goodbye.\n");
	return 0;
}