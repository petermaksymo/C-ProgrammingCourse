#include <stdio.h>

int convertBinaryToDecimal(int numBinary);
int convertDecimalToBinary(int numDecimal);

//This function will prompt user for inputs and conversion choice, outputting original and converted number
int main(void) {
	char conversionChoice;
	int usrInput;
	
	printf("Enter B for conversion of Binary to Decimal, OR\n"
			"Enter D for conversion of Decimal to Binary: ");
	scanf(" %c", &conversionChoice);
	printf("Enter your number: ");
	scanf(" %d", &usrInput);
	
	//This will choose the converter or print an error message for invalid inputs
	if (conversionChoice == 'B') {
		printf("%d in binary = %d in decimal\n", usrInput, convertBinaryToDecimal(usrInput));
	} else if (conversionChoice == 'D') {
			printf("%d in decimal = %d in binary\n", usrInput, convertDecimalToBinary(usrInput));
	} else {
			printf(" Invalid input; Goodbye");
	}
	
	return 0;
}

//This converts binary to decimal
int convertBinaryToDecimal (int numBinary){
	int wrkingNumDecimal = 0, base = 1, lastDigit, wrkngNumBinary;
	wrkngNumBinary = numBinary;
	
	//Loop runs systematically through each digit
	while (wrkngNumBinary > 0) {
		/*finds the last digit (remainder), multiplies it by a growing base and adds
		to working decimal number, and then will drop the last digit*/
		lastDigit = wrkngNumBinary % 10;
		wrkingNumDecimal = base * lastDigit + wrkingNumDecimal;
		base = base * 2;
		wrkngNumBinary = wrkngNumBinary / 10;
	}
	
	return wrkingNumDecimal;
}

//This converts decimal to binary
int convertDecimalToBinary (int numDecimal) {
	int wrkngNumDecimal, wrkngNumBinary = 0, digitPlacer = 1;
	
	wrkngNumDecimal = numDecimal;
	
	//Loop runs through using repeated division by 2 method
	while (wrkngNumDecimal > 0) {
		
		/*the remainder is the digit, so if it is 1, it will be placed with digitPlacer
		  then the working decimal number is divided by 2*/
		if(wrkngNumDecimal % 2 == 1) {
			wrkngNumBinary = wrkngNumBinary + digitPlacer;
		} 
		
		//Will update digitPLacer to next digit and the working number
		digitPlacer = digitPlacer * 10;
		wrkngNumDecimal = wrkngNumDecimal / 2;
	}
	
	return (wrkngNumBinary);
}


