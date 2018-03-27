#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
 
void setupBoard (char board[][26], int boardSize);
void printBoard(char board[][26], int boardSize);
bool positionInBounds(int boardSize, char row, char col); 
bool isLegalMove(char board[][26], int boardSize, char colour, char row, char col);
bool checkLegalInDirection(char board[][26], int boardSize, char row, char col, char colour, int deltaRow, int deltaCol);
bool moveAvailable(char board[][26], int boardSize, char colour);
void makeMove(char board[][26], int boardSize, char colour, char row, char col);
int moveScore(char board[][26], int boardSize, char colour, char row, char col);
void compMove(char board[][26], int boardSize, char colour);
void endGame(char board[][26], int boardSize);
void isGameDone(char board[][26], int boardSize);

int main(void) {
	int boardSize;
	char board[26][26];
	char compColour, row, col;
	
	//basic startup for the board
	printf("Enter the board dimension: ");
	scanf("%d", &boardSize);
	
	setupBoard(board, boardSize);
	
	printf("Computer plays (B/W) : ");
	scanf(" %c" ,&compColour);
	printBoard(board, boardSize);
	
	
	//The actual game, will run as long as moves are available
	while(moveAvailable(board, boardSize, 'W') || moveAvailable(board, boardSize, 'B')) {
		if(compColour == 'W') {
			
			//will check if it should end game first
			isGameDone(board, boardSize);
			if (moveAvailable(board, boardSize, 'B')){
				//asks for move, gets move, makes move, prints board
				printf("Enter move for colour B (RowCol): ");
				scanf(" %c%c" ,&row, &col);
				makeMove(board, boardSize, 'B', row, col);
				printBoard(board, boardSize);
			} else {
				//if there is not available move, will print no valid move
				printf("B player has no valid move.\n");
			}
			
			isGameDone(board, boardSize);
			if (moveAvailable(board, boardSize, 'W')){
				compMove(board, boardSize, 'W');
				printBoard(board, boardSize);
			} else {
				printf("W player has no valid move.\n");
			}
			
		//for the other colour
		} else if(compColour == 'B') {
			
			isGameDone(board, boardSize);
			if (moveAvailable(board, boardSize, 'B')){
				compMove(board, boardSize, 'B');
				printBoard(board, boardSize);
			} else {
				printf("B player has no valid move.\n");
			}
			
			isGameDone(board, boardSize);
			if (moveAvailable(board, boardSize, 'W')){
				printf("Enter move for colour W (RowCol): ");
				scanf(" %c%c" ,&row, &col);
				makeMove(board, boardSize, 'W', row, col);
				printBoard(board, boardSize);
			} else {
				printf("W player has no valid move.\n");
			}
			
		}
	}
	
	//if no moves available and game did not end, it will end here (failsafe)
	endGame(board, boardSize);
	return 0;
}
	
//initial setup for board at beginning of game
void setupBoard (char board[][26], int boardSize) {
	int wrkingRow, wrkingCol;
		
	//Sets up board given valid input
	if (boardSize % 2 != 0 || boardSize < 2 ||boardSize > 26) {
		printf("Error, invalid board size.\n");
		exit(0);
	}
	//populates spots in boundaries with 'U'
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
}

//will print the board
void printBoard(char board[][26], int boardSize) {
	//first row (letters for col)
	printf("  ");
	for (char colLetter = 'a'; colLetter - 'a' < boardSize; colLetter++) {
		printf("%c", colLetter);
	}
	
	//the rest, does the letter for row first
	for (int wrkingRow = 0; wrkingRow < boardSize; wrkingRow ++) {
		char rowLetter = wrkingRow + 'a';
		printf("\n%c ", rowLetter);
		
		//here it prints the row of the board values
		for (int wrkingCol = 0; wrkingCol < boardSize; wrkingCol ++) {
			printf("%c", board[wrkingRow][wrkingCol]);
		}
	}
	printf("\n");
}

//checks if position is within bounds
bool positionInBounds(int boardSize, char row, char col) {
	return (row - 'a' < boardSize && col - 'a' < boardSize && row >= 'a' && col >= 'a');
}

//checks if a specific location is a legal move
//looks if its in bounds, unoccupied and then looks for validity
bool isLegalMove(char board[][26], int boardSize, char colour, char row, char col) {
	if (positionInBounds(boardSize, row, col)) {
		if (board[row-'a'][col-'a'] == 'U') {
			//sweeps each possible direction
			for (int deltaRow = -1; deltaRow <= 1; deltaRow ++) {
				for (int deltaCol = -1; deltaCol <= 1; deltaCol ++) {
					//if statement makes sure it doesnt look on its own tile
					if (deltaRow != 0 || deltaCol != 0) {
						//only need to be legal in one direction to be true
						if (checkLegalInDirection(board, boardSize, row, col, colour, deltaRow, deltaCol)) {
							return true;
						}
					}
				}
			}
		}
	}
	//returns false if it can't find anything legal
	return false;
}

//checks if the move is legal in a specific direction
bool checkLegalInDirection(char board[][26], int boardSize, char row, char col, char colour, int deltaRow, int deltaCol) { 
	if (colour == 'W') {
		//uses i as a distance counter, makes sure everything is in bounds first
		//runs as long as the colour is opposite to the one being checks, returns true if the next tile is W and in bounds
		for(int i = 1; positionInBounds(boardSize, row+deltaRow*i, col+deltaCol*i) && board[row-'a'+deltaRow*i][col-'a'+deltaCol*i] == 'B'; i ++) {
			if (positionInBounds(boardSize, row+deltaRow*(i+1), col+deltaCol*(i+1)) && board[row-'a'+deltaRow*(i+1)][col-'a'+deltaCol*(i+1)] == 'W') {
			return true;
			}
		}
		
	} else if (colour == 'B') {
		for(int i = 1; positionInBounds(boardSize, row+deltaRow*i, col+deltaCol*i) && board[row-'a'+deltaRow*i][col-'a'+deltaCol*i] == 'W'; i ++) {
			if (positionInBounds(boardSize, row+deltaRow*(i+1), col+deltaCol*(i+1)) && board[row-'a'+deltaRow*(i+1)][col-'a'+deltaCol*(i+1)] == 'B') {
			return true;
			}
		}
	}
	
	//if it isnt legal, returns false
	return false;
}
	
//checks if there are any available moves left for a given colour
bool moveAvailable(char board[][26], int boardSize, char colour) {
	//sweeps every tile in the board
	for(char wrkingRow = 'a'; wrkingRow - 'a' < boardSize; wrkingRow ++) {
		for(char wrkingCol = 'a'; wrkingCol - 'a' < boardSize; wrkingCol ++) {
			//adds effeciency by only looking at unoccupied tiles
			if(board[wrkingRow-'a'][wrkingCol-'a'] == 'U') {
				// if it finds a legal move, will return true
				if(isLegalMove(board, boardSize, colour, wrkingRow, wrkingCol)) {
					return true;
				}
			}
		}
	}
	return false;
}

//will make the move for the user, and flip the tiles
void makeMove(char board[][26], int boardSize, char colour, char row, char col) {
	//makes sure its legal
	if (isLegalMove(board, boardSize, colour, row, col)) {
		//places the tile
		board[row-'a'][col-'a'] = colour;
		
		//sweeps each direction around the tile
		for (int deltaRow = -1; deltaRow <= 1; deltaRow ++) {
			for (int deltaCol = -1; deltaCol <= 1; deltaCol ++) {
				//makes sure it doesnt look on itself
				if (deltaRow != 0 || deltaCol != 0) {
					//looks in the direction, makes sure its legal and will flip all opposite coloured tiles
					//until it find one that is the same colour
					if (colour == 'W' && checkLegalInDirection(board, boardSize, row, col, colour, deltaRow, deltaCol)) {
						for (int i = 1; board[row-'a'+deltaRow*i][col-'a'+deltaCol*i] == 'B'; i++) {
							board[row-'a'+deltaRow*i][col-'a'+deltaCol*i] = 'W';
						}
					} else if (colour == 'B' && checkLegalInDirection(board, boardSize, row, col, colour, deltaRow, deltaCol)) {
						for (int i = 1; board[row-'a'+deltaRow*i][col-'a'+deltaCol*i] == 'W'; i++) {
							board[row-'a'+deltaRow*i][col-'a'+deltaCol*i] = 'B';
						}
					}
				}
			}
		}
	//if the move is invalid, will tell user and end game
	} else {
		printf("Invalid move.\n");
		endGame(board, boardSize);
	}
}

//Used to calculate the number of tiles which would be flipped
int moveScore(char board[][26], int boardSize, char colour, char row, char col) {
	int score = 0, flips;
	//looks in each direction
	for (int deltaRow = -1; deltaRow <= 1; deltaRow ++) {
		for (int deltaCol = -1; deltaCol <= 1; deltaCol ++) {
			//will not look on its own tile
			if (deltaRow != 0 || deltaCol != 0) {
				//check if direction is legal, then flips increases for every consecutive opposite colour
				flips = 0;
				if (colour == 'W') {
					if (checkLegalInDirection(board, boardSize, row, col, colour, deltaRow, deltaCol)){
						do {
							flips ++;
						} while(board[row-'a'+deltaRow*flips][col-'a'+deltaCol*flips] == 'B');
					}
				} else if (colour == 'B') {
					if (checkLegalInDirection(board, boardSize, row, col, colour, deltaRow, deltaCol)){
						do {
							flips ++;
						} while(board[row-'a'+deltaRow*flips][col-'a'+deltaCol*flips] == 'W');
					}
				}
				score = score + flips;
			}
		}
	}
	return (score);
}

//handles the computer's move
void compMove(char board[][26], int boardSize, char colour) {
	int maxScore = 0;
	char maxScoreRow, maxScoreCol;
	
	//sweeps the board
	for(char wrkingRow = boardSize+'a'; wrkingRow >= 'a'; wrkingRow--) {
		for(char wrkingCol = boardSize+'a'; wrkingCol >= 'a'; wrkingCol--) {
			//has to be legal and have a greater move score than any previous move to change the max row/col variables
			if(isLegalMove(board, boardSize, colour, wrkingRow, wrkingCol) && moveScore(board, boardSize, colour, wrkingRow, wrkingCol) >= maxScore) {
				maxScore = moveScore(board, boardSize, colour, wrkingRow, wrkingCol);
				maxScoreRow = wrkingRow;
				maxScoreCol = wrkingCol;
			}
		}
	}
	//makes the move given the mac row/col variables
	makeMove(board, boardSize, colour, maxScoreRow, maxScoreCol);
	printf("Computer places %c at %c%c.\n", colour, maxScoreRow, maxScoreCol);
}

//ends the game
void endGame(char board[][26], int boardSize) {
	int blackScore = 0, whiteScore = 0;
	//finds the scores by sweeping the board
	for(int row = 0; row < boardSize; row ++) {
		for(int col = 0; col < boardSize; col ++) {
			if (board[row][col] == 'B'){
				blackScore++;
			} else if (board[row][col] == 'W') {
				whiteScore++;
			}
		}
	}
	
	//compares the black score to white score printing the winner
	if (blackScore > whiteScore) {
		printf("B player wins.\n");
	} else if (blackScore == whiteScore) {
		printf("Draw!\n");
	} else if (whiteScore > blackScore) {
		printf("W player wins.\n");
	}
	
	//exit is used to exit the while program
	exit(0);
}

//looks if the game is done, will end the game if it is done
void isGameDone(char board[][26], int boardSize) {
	if (!moveAvailable(board, boardSize, 'B') && !moveAvailable(board, boardSize,'W')) {
		endGame(board, boardSize);
	}
}