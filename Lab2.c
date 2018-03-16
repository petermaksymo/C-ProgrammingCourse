#include <stdio.h>

int main(void) {
	//The variables and constants used, band3 represents the multiplier band and band4 is the tolerance band
	char ClrBand1, ClrBand2, ClrBand3, ClrBand4;
	double numBand1, numBand2, numBand3, numBand4;
	const int ohmToKOhm = 1000, ohmToMOhm = 1000000, digitShiftLeft = 10;
	
	//Asks the user for input for the 4 bands
	printf("Please enter the 1st band:\n");
	scanf(" %c", &ClrBand1);
	printf("Please enter the 2nd band:\n");
	scanf(" %c", &ClrBand2);
	printf("Please enter the multiplier band:\n");
	scanf(" %c", &ClrBand3);
	printf("Please enter the tolerance band:\n");
	scanf(" %c", &ClrBand4);
	
	//initiallizes a print statement, will continue in each switch case
	printf("Resistor bands: ");
	
	//each switch assigns a number value to numBand_ and continues the print statement with the colour name
	switch(ClrBand1) {
		case('K'):
		case('k'): numBand1 = 0; 
				printf("Black ");
			break;
			
		case('B'):
		case('b'): numBand1 = 1; 
				printf("Brown ");
			break;
			
		case('R'):
		case('r'): numBand1 = 2;
				printf("Red ");
			break;
			
		case('O'):
		case('o'): numBand1 = 3;
				printf("Orange ");
			break;
			
		case('E'):
		case('e'): numBand1 = 4; 
				printf("Yellow ");
			break;
			
		case('G'):
		case('g'): numBand1 = 5;
				printf("Green ");
			break;
			
		case('U'):
		case('u'): numBand1 = 6;
				printf("Blue ");
			break;
			
		case('V'):
		case('v'): numBand1 = 7;
				printf("Violet ");
			break;
			
		case('Y'):
		case('y'): numBand1 = 8;
				printf("Grey ");
			break;
			
		case('W'):
		case('w'): numBand1 = 9;
				printf("White ");
			break;
	}
	switch(ClrBand2) {
		case('K'):
		case('k'): numBand2 = 0; 
				printf("Black ");
			break;
			
		case('B'):
		case('b'): numBand2 = 1; 
				printf("Brown ");
			break;
			
		case('R'):
		case('r'): numBand2 = 2;
				printf("Red ");
			break;
			
		case('O'):
		case('o'): numBand2 = 3;
				printf("Orange ");
			break;
			
		case('E'):
		case('e'): numBand2 = 4; 
				printf("Yellow ");
			break;
			
		case('G'):
		case('g'): numBand2 = 5;
				printf("Green ");
			break;
			
		case('U'):
		case('u'): numBand2 = 6;
				printf("Blue ");
			break;
			
		case('V'):
		case('v'): numBand2 = 7;
				printf("Violet ");
			break;
			
		case('Y'):
		case('y'): numBand2 = 8;
				printf("Grey ");
			break;
			
		case('W'):
		case('w'): numBand2 = 9;
				printf("White ");
			break;
	}
	switch(ClrBand3) {
		case('K'):
		case('k'): numBand3 = 1; 
				printf("Black ");
			break;
			
		case('B'):
		case('b'): numBand3 = 10; 
				printf("Brown ");
			break;
			
		case('R'):
		case('r'): numBand3 = 100;
				printf("Red ");
			break;
			
		case('O'):
		case('o'): numBand3 = 1000;
				printf("Orange ");
			break;
			
		case('E'):
		case('e'): numBand3 = 10000; 
				printf("Yellow ");
			break;
			
		case('G'):
		case('g'): numBand3 = 100000;
				printf("Green ");
			break;
			
		case('U'):
		case('u'): numBand3 = 1000000;
				printf("Blue ");
			break;
			
		case('V'):
		case('v'): numBand3 = 10000000;
				printf("Violet ");
			break;
			
		case('L'):
		case('l'): numBand3 = 0.1;
				printf("Gold ");
			break;
			
		case('S'):
		case('s'): numBand3 = 0.01;
				printf("Silver ");
			break;
	}
	switch(ClrBand4) {
		case('B'):
		case('b'): numBand4 = 1; 
				printf("Brown\n");
			break;
			
		case('R'):
		case('r'): numBand4 = 2;
				printf("Red\n");
			break;
		case('G'):
		case('g'): numBand4 = 0.5;
				printf("Green\n");
			break;
			
		case('U'):
		case('u'): numBand4 = 0.25;
				printf("Blue\n");
			break;
			
		case('V'):
		case('v'): numBand4 = 0.10;
				printf("Violet\n");
			break;
			
		case('Y'):
		case('y'): numBand4 = 0.05;
				printf("Grey\n");
			break;
			
		case('L'):
		case('l'): numBand4 = 5;
				printf("Gold\n");
			break;
			
		case('S'):
		case('s'): numBand4 = 10;
				printf("Silver\n");
			break;
	}
	
	//nested if statements will convert resistance to KOhms or MOhms if needed and print the resistance
	double resistTotal = (numBand1*digitShiftLeft+numBand2)*numBand3;
	if (resistTotal < ohmToKOhm) {
		printf("Resistance: %.2lf Ohms +/- %.2lf%%\n",resistTotal, numBand4);
	}else if (resistTotal < ohmToMOhm) {
			resistTotal = resistTotal/ohmToKOhm;
			printf("Resistance: %.2lf KOhms +/- %.2lf%%\n",resistTotal, numBand4);
	}else {
			resistTotal = resistTotal/ohmToMOhm;
			printf("Resistance: %.2lf MOhms +/- %.2lf%%\n",resistTotal, numBand4);
	}
	return 0;
}