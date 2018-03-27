#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
 
void printBoard(char board[][26], int n); 
bool positionInBounds(int boardSize, char row, char col);
bool checkLegalInDirection(char board[][26], int boardSize, char row, char col, char colour, int deltaRow, int deltaCol);
void availableMoves(char board[][26], int boardSize, char colour);

 
int main(void) {
	int boardSize, wrkingRow, wrkingCol;
	char board[26][26];
	
	//Sets up board given valid input
	printf("Enter the board dimension: ");
	scanf("%d", &boardSize);
	if (boardSize % 2 != 0 || boardSize < 2 ||boardSize > 26) {
		printf("Error, invalid board size.\n");
		return 0;
	}
	
	//populates board with 'U'
	for (wrkingRow = 0; wrkingRow < boardSize; wrkingRow ++) {
		for (wrkingCol = 0; wrkingCol < boardSize; wrkingCol ++) {
			board[wrkingRow][wrkingCol] = 'U';
		}
	}
	
	//sets up the middle 4 pieces
	board[boardSize/2-1][boardSize/2-1] = 'W';
	board[boardSize/2][boardSize/2] = 'W';
	board[boardSize/2-1][boardSize/2] = 'B';
	board[boardSize/2][boardSize/2-1] = 'B';
	
	printBoard(board, boardSize);
	
	//Configuration of board
	printf("Enter board configuration:\n");
	char colour, row, col;
	
	//Scans for input and places them. '!!!' terminates this step
	//It is assumed that all input is valid here
	scanf(" %c%c%c", &colour, &row, &col);
	while(colour != '!' && row != '!' && col != '!') {
		board[row-'a'][col-'a'] = colour;
		scanf(" %c%c%c", &colour, &row, &col);
	}
	
	printBoard(board, boardSize);
	
	availableMoves(board, boardSize, 'W');
	availableMoves(board, boardSize, 'B');
	
	//This part will prompt for a move, and if it is legal, will make the move
	printf("Enter a move:\n");
	scanf(" %c%c%c", &colour, &row, &col);
	
	bool legalMove = false;
	if (positionInBounds(boardSize, row, col) && board[row-'a'][col-'a'] == 'U') {
		//will check if its legal for each direction
		for (int deltaRow = -1; deltaRow <= 1; deltaRow ++) {
			for (int deltaCol = -1; deltaCol <= 1; deltaCol ++) { 
				//makes sure it doesnt check its own tile
				if (deltaRow != 0 || deltaCol != 0) {
					//checks if legal first, then will make the move if it is legal
					if(checkLegalInDirection(board, boardSize, row, col, colour, deltaRow, deltaCol)) {
						legalMove = true;
						//Since it knows its legal, it can just flip every tile which has the opposite colour. It stops when it reaches a tile 
						//with the same colour (for a move for 'W', will stop at the next 'W' tile...
						if (colour == 'W') {
							for (int distance = 1; board[row-'a'+deltaRow*distance][col-'a'+deltaCol*distance] == 'B'; distance ++ ) {
								board[row-'a'+deltaRow*distance][col-'a'+deltaCol*distance] = 'W';
							}
						} else if (colour == 'B') {
							for (int distance = 1; board[row-'a'+deltaRow*distance][col-'a'+deltaCol*distance] == 'W'; distance ++ ) {
								board[row-'a'+deltaRow*distance][col-'a'+deltaCol*distance] = 'B';
							}
						}
					}
				}
			}
		}
	}
	//if its legal, will place the peice (all the flips were carried out before)
	if (legalMove) {
		printf("Valid move.\n");
		board[row-'a'][col-'a'] = colour;
	} else {
		printf("Invalid move.\n");
	}	
	printBoard(board, boardSize);
	
	return 0;
}

//Prints the current board
void printBoard(char board[][26], int n) {
	//For the collumn names:
	printf("  ");
	for (char colLetter = 'a'; colLetter - 'a' < n; colLetter++) {
		printf("%c", colLetter);
	}
	
	//For the other rows:
	for (int wrkingRow = 0; wrkingRow < n; wrkingRow ++) {
		char rowLetter = wrkingRow + 'a';
		printf("\n%c ", rowLetter);
		for (int wrkingCol = 0; wrkingCol < n; wrkingCol ++) {
			printf("%c", board[wrkingRow][wrkingCol]);
		}
	}
	printf("\n");
}

//Will check if the move is within the board
bool positionInBounds(int boardSize, char row, char col) {
	return row - 'a' < boardSize && col - 'a' < boardSize && row >= 'a' && col >= 'a';
}

//Checks if a move is legal in a certain direction
bool checkLegalInDirection(char board[][26], int boardSize, char row, char col, char colour, int deltaRow, int deltaCol) { 
	if (colour == 'W') {
		int distance = 1;
		while (board[row-'a'+deltaRow*distance][col-'a'+deltaCol*distance] == 'B') {
			//checks if the next tile is the same as the colour of move
			if (board[row-'a'+deltaRow*(distance+1)][col-'a'+deltaCol*(distance+1)] == 'W') {
			return true;
			}
		distance ++;
		}
	} else if (colour == 'B') {
		int distance = 1;
		while (board[row-'a'+deltaRow*distance][col-'a'+deltaCol*distance] == 'W') {
			if (board[row-'a'+deltaRow*(distance+1)][col-'a'+deltaCol*(distance+1)] == 'B') {
			return true;
			}
		distance ++;
		}
	}
	return false;
}

//Prints the moves available for a given colour
void availableMoves(char board[][26], int boardSize, char colour) {
	if (colour == 'B') {
		printf("Available moves for B:\n");
	} else if (colour == 'W') {
		printf("Available moves for W:\n");
	}
	
	//looks at each tile starting at top left, working along cols, then rows
	for(char row = 'a'; row - 'a' < boardSize; row++) {
		for(char col = 'a'; col - 'a' < boardSize; col++) {
			if (board[row-'a'][col-'a'] == 'U') {
				bool legalMove = false;
				//checks for each direction
				for (int deltaRow = -1; deltaRow <= 1; deltaRow ++) {
					for (int deltaCol = -1; deltaCol <= 1; deltaCol ++) {
						//makes sure it doesnt check its own tile
						if (deltaRow != 0 || deltaCol != 0) {
							if(checkLegalInDirection(board, boardSize, row, col, colour, deltaRow, deltaCol)) {
								legalMove = true;
							}
						}
					}
				}
				
				if (legalMove) {
				printf("%c%c\n", row,col);
				}
			}
		}
	}
}