#include <stdio.h>

int main(void) {
	double numberOne, numberTwo, result;
	char operation;
	
	//Initial prompts for user
	printf("Enter first number: ");
	scanf(" %lf", &numberOne);
	printf("Enter second number: ");
	scanf(" %lf", &numberTwo);
	printf("Enter calculation command (one of a, s, m, or d): ");
	scanf(" %c", &operation);
	
	//This will run through the different cases of user input and output expected results
	if(operation == 'a') {
		result = numberOne + numberTwo;
		printf("Sum of %.2lf and %.2lf is %.2lf\n", numberOne, numberTwo, result);
	} else if(operation == 's') {
		result = numberOne - numberTwo;
		printf("Difference of %.2lf from %.2lf is %.2lf\n", numberOne, numberTwo, result);
	} else if(operation == 'm') {
		result = numberOne * numberTwo;
		printf("Product of %.2lf and %.2lf is %.2lf\n", numberOne, numberTwo, result);
	} else if(operation == 'd') {
		//This if statement will print the error when dividing by 0
		if(numberTwo == 0){
			printf("Error, trying to divide by zero\n");
		} else {
		result = numberOne / numberTwo;
		printf("Division of %.2lf by %.2lf is %.2lf\n", numberOne, numberTwo, result);
		}
	//This message will be the default when an invalid operator is used
	} else {
		printf("Error, unknown calculation command given\n");
	}
	return 0;
}