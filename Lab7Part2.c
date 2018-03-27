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
int tilesToFlip(char board[][26], int boardSize, char colour, char row, char col);
void compMove(char board[][26], int boardSize, char colour, int scoreBoard[][26], char dummyBoard[][26]);
void endGame(char board[][26], int boardSize);
void isGameDone(char board[][26], int boardSize);
void generateBoardScores(char board[][26], int boardSize, int scoreBoard[][26]);
void copyBoard(char board[][26], int boardSize, char dummyBoard[26][26]);
bool lookAhead(char board[][26], int boardSize, char colour, char row, char col, char dummyBoard[26][26]);

int main(void) {
	int boardSize;
	char board[26][26], dummyBoard[26][26];
	char compColour, row, col;
	int scoreBoard[26][26];
	
	//initial setup
	printf("Enter the board dimension: ");
	scanf("%d", &boardSize);
	
	setupBoard(board, boardSize);
	
	printf("Computer plays (B/W) : ");
	scanf(" %c" ,&compColour);
	printBoard(board, boardSize);
	generateBoardScores(board, boardSize, scoreBoard);
	
	//Runs the game as long as moves are still available
	while(moveAvailable(board, boardSize, 'W') || moveAvailable(board, boardSize, 'B')) {
		if(compColour == 'W') {
			
			//user's turn:
			//checks if it should end game (no moves available)
			isGameDone(board, boardSize);
			if (moveAvailable(board, boardSize, 'B')){
				printf("Enter move for colour B (RowCol): ");
				scanf(" %c%c" ,&row, &col);
				makeMove(board, boardSize, 'B', row, col);
				printBoard(board, boardSize);
			} else {
				printf("B player has no valid move.\n");
			}
			
			//computer's turn:
			isGameDone(board, boardSize);
			if (moveAvailable(board, boardSize, 'W')){
				compMove(board, boardSize, 'W', scoreBoard, dummyBoard);
				printBoard(board, boardSize);
			} else {
				printf("W player has no valid move.\n");
			}
		} else if(compColour == 'B') {
			
			isGameDone(board, boardSize);
			if (moveAvailable(board, boardSize, 'B')){
				compMove(board, boardSize, 'B', scoreBoard, dummyBoard);
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
	
	//failsafe to end the game if the isGameDone function did not already do it
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

//prints the board
void printBoard(char board[][26], int boardSize) {
	//The first row, with the col letters
	printf("  ");
	for (char colLetter = 'a'; colLetter - 'a' < boardSize; colLetter++) {
		printf("%c ", colLetter);
	}
	
	//the rest, first doing the row letters
	for (int wrkingRow = 0; wrkingRow < boardSize; wrkingRow ++) {
		char rowLetter = wrkingRow + 'a';
		printf("\n\n%c ", rowLetter);
		
		//and here it prints the row of the board
		for (int wrkingCol = 0; wrkingCol < boardSize; wrkingCol ++) {
			printf("%c ", board[wrkingRow][wrkingCol]);
		}
	}
	printf("\n");
}

//checks if a specific location is a legal move
//looks if its in bounds, unoccupied and then looks for validity
bool positionInBounds(int boardSize, char row, char col) {
	return (row - 'a' < boardSize && col - 'a' < boardSize && row >= 'a' && col >= 'a');
}

//checks if a move is legal
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
	//makes sure its legal first
	while (!isLegalMove(board, boardSize, colour, row, col)) {
		printf("Invalid move.\n");
		printf("Enter another move (RowCol): ");
		scanf(" %c%c" ,&row, &col);
	}
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
	//if the move is invalid, will tell user and end gam
	//} else {
		//printf("Invalid move.\n");
		//endGame(board, boardSize);
	//}
}

//Used to calculate the number of tiles which would be flipped
int tilesToFlip(char board[][26], int boardSize, char colour, char row, char col) {
	int score = 0;
	for (int deltaRow = -1; deltaRow <= 1; deltaRow ++) {
		for (int deltaCol = -1; deltaCol <= 1; deltaCol ++) {
			if (deltaRow != 0 || deltaCol != 0) {
				//score increases if tile in direction is different colour and the tile after is not yet same colour
				int i = 1;
				if (colour == 'W') {
					while(positionInBounds(boardSize, row+deltaRow*i, col+deltaCol*i) && board[row-'a'+deltaRow*i][col-'a'+deltaCol*i] == 'B' 
					&& board[row-'a'+deltaRow*(i+1)][col-'a'+deltaCol*(i+1)] != 'W') {
						i ++;
					}
				} else if (colour == 'B') {
					while(positionInBounds(boardSize, row+deltaRow*i, col+deltaCol*i) && board[row-'a'+deltaRow*i][col-'a'+deltaCol*i] == 'W'
					&& board[row-'a'+deltaRow*(i+1)][col-'a'+deltaCol*(i+1)] != 'B') {
						i ++;
					}
				}
				//i is number of tiles to be flipped minus 1 (hence the + 1)
				score = score + i + 1;
			}
		}
	}
	return (score);
}

//handles the computer's move
void compMove(char board[][26], int boardSize, char colour, int scoreBoard[][26], char dummyBoard[][26]) {
	//since there can be negative scores, maxScore is set much lower than any possible move
	int maxScore = -100000;
	char maxScoreRow, maxScoreCol;
	
	//sweeps the board
	for(char wrkingRow = boardSize+'a'; wrkingRow >= 'a'; wrkingRow--) {
		for(char wrkingCol = boardSize+'a'; wrkingCol >= 'a'; wrkingCol--) {
			//This is the total move score, makes sure the move is legal and then checks score
			//Score is computed by using summing its position on the scoreBoard and the tiles it would flip
			if(isLegalMove(board, boardSize, colour, wrkingRow, wrkingCol) 
			&& (tilesToFlip(board, boardSize, colour, wrkingRow, wrkingCol) + scoreBoard[wrkingRow-'a'][wrkingCol-'a']) >= maxScore) {
				//will change the variables which store the max information if it is a better move
				maxScore = (tilesToFlip(board, boardSize, colour, wrkingRow, wrkingCol) + scoreBoard[wrkingRow-'a'][wrkingCol-'a']);
				maxScoreRow = wrkingRow;
				maxScoreCol = wrkingCol;
			}
			
			//This is an override where it makes the move on a dummy board and checks if the opponent has
			//a move available to make, if its true, it will make that move
			if (lookAhead(board, boardSize, colour, wrkingRow, wrkingCol, dummyBoard)) {
				makeMove(board, boardSize, colour, wrkingRow, wrkingCol);
				return;
			}
		}
	}
	//makes max score move if override was not triggered
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

//generates the scoreBoard array with scores assigned for each tile
//The corners are most valuable while ones around it are least valuable, likewise, the edges are next most
//valuable while the edges adjacent to the outer edges are worth negative again
//the rest are then just given a default value of 50
void generateBoardScores(char board[][26], int boardSize, int scoreBoard[][26]) {
	for (int row = 0; row <boardSize; row ++) {
		for(int col = 0; col < boardSize; col ++) {
			
			//it might need to work from the outside in
			
			//corners:
			if ((row == 0 || row == boardSize-1) && (col == 0 || col == boardSize-1)){
				scoreBoard[row][col] = 10000;
			//inner corners:
			} else if ((row == 1 || row == boardSize-2) && (col == 1 || col == boardSize-2)) {
				scoreBoard[row][col] = -5000;
			//edges beside corners:
			} else if ((row == 0 || row ==  boardSize-1) && (col == 1 || col == boardSize-2)){
				scoreBoard[row][col] = -3000;
			} else if ((row == 1 || row == boardSize-2) && (col == 0 || col == boardSize-1)){
				scoreBoard[row][col] = -3000;
			//inner tiles, 3 away from the corner on the outer edge:
			} else if ((row == 0 || row == boardSize-1) && (col == 2 || col == boardSize-3)){
				scoreBoard[row][col] = 1000;
			} else if ((row == 2 || row == boardSize-3) && (col == 0 || col == boardSize-1)){
				scoreBoard[row][col] = 1000;
			//remaining edges:
			} else if (row == 0 || row == boardSize - 1) {
				scoreBoard[row][col] = 800;
			} else if (col == 0 || col == boardSize - 1) {
				scoreBoard[row][col] = 800;
			//inner edges
			} else if (row == 1 || row == boardSize -2) {
				scoreBoard[row][col] = -500;
			} else if (col == 1 || col == boardSize -2) {
				scoreBoard[row][col] = -500;
			} else {
				scoreBoard[row][col] = 50;
			}
		}
	}
}

//copies the board to the dummyBoard
void copyBoard(char board[][26], int boardSize, char dummyBoard[26][26]) {
	for (int row = 0; row < boardSize; row++) {
		for (int col = 0; col < boardSize; col++) {
			dummyBoard[row][col] = board[row][col];
		}
	}
}

//Looks ahead and returns true if that move results in the opponent having no move to make
bool lookAhead(char board[][26], int boardSize, char colour, char row, char col, char dummyBoard[26][26]){
	if(isLegalMove(board, boardSize, colour, row, col)) {
		copyBoard(board, boardSize, dummyBoard);
		makeMove(dummyBoard, boardSize, colour, row, col);
		return (colour == 'B' && !moveAvailable(dummyBoard, boardSize, 'W')) || (colour == 'W' && !moveAvailable(dummyBoard, boardSize, 'B'));
	}
	return false;
}