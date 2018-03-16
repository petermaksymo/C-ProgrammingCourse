#include <stdio.h>

int main(void) {
	int totalRows, totalCols, workingRow, workingCol, midCol;
	const int minRows = 1, maxRows = 20;
	
	printf("Enter the number of rows in the triangle: ");
	scanf("%d", &totalRows);
	
	totalCols = totalRows*2-1;
	midCol = totalRows;
	
	//will first check if input is valid, if not then will print error message
	if (totalRows < minRows || totalRows > maxRows) {
		printf("Error, invalid input.\n");
	} else {
	//initial loop so program runs for each row
		for (workingRow = 1; workingRow <= totalRows; workingRow ++) {
			
			//this loop is for printing each collumn
			for (workingCol = 1; workingCol <= totalCols; workingCol ++) {
				//printing on the edges
				if (workingCol == midCol-(workingRow-1) || workingCol == midCol+(workingRow-1)) {
					printf("^");
				//printing the bottom row
				} else if (workingRow == totalRows) {
					printf("^");
				//if it is not in a valid space to print "^", it will print a <space>
				} else {
					printf(" ");
				}
			}
			printf("\n");
		}
	}
	return 0;
}
