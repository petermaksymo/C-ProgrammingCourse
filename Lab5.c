#include <stdio.h>
#include <stdbool.h>

int triangle(int numRows);
int spaces (int numSpaces);
int choose(int row, int numInRow);
int factorial(int numOfFactorial);

//Will print Pascal's Triangle given a valid input
int main(void) {
	int numRows;
	bool inputValid = true;
	
	while (inputValid) {
		printf("Enter the number of rows: ");
		scanf(" %d", &numRows);
		
		if (numRows >= 0 && numRows <= 13) {
			triangle(numRows);
		} else {
			inputValid = false;
		}
	}
	
	return 0;
}

//function to print Pascal's Triangle
int triangle(int numRows) {
	int maxCol, numToPrint;
	const int threeDigits = 100, twoDigits = 10;
	
	maxCol = numRows * 6 - 5;
	
	//loop for the working row
	for(int wrkingRow = 1; wrkingRow <= numRows; wrkingRow ++) {
		int toFirstNum = (maxCol - 1) / 2 - (3 * (wrkingRow - 1));
		spaces(toFirstNum);
		
		//will print the numbers in row and add amount of spaces
		for(int numInRow = wrkingRow; numInRow > 0; numInRow --) {
			numToPrint = choose(wrkingRow - 1, numInRow - 1);
			printf("%d", numToPrint);
				if(numToPrint >= threeDigits) {
					spaces(3);
				} else if(numToPrint >= twoDigits) {
					spaces(4); 
				} else {
					spaces(5);
				}
		}
		
		printf("\n");
	}
	return 0;
}

//function to print x amount of spaces
int spaces(int numSpaces) {
	for(int wrkingNum = 1; wrkingNum <= numSpaces; wrkingNum ++) {
		printf(" ");
	}
	return 0;
}

//choose function 
int choose(int row, int numInRow) {
	return(factorial(row) / (factorial(numInRow)*factorial(row-numInRow)));
}

//factorial function
int factorial(int numOfFactorial) { 
	int result = 1;
	for(int wrkingNum = 1; wrkingNum <= numOfFactorial; wrkingNum ++) {
		result = result * wrkingNum;
	}
	
	return(result);
}