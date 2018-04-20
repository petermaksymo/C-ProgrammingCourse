//
// APS105 Lab 8 Lab8.c
//
// This is a program written to maintain a personal music library, 
// using a linked list to hold the songs in the library.
//
// Author: Peter Maksymowsky
// Student Number: 1004401756
//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

// A node in the linked list

// Each string in the node is declared as a character pointer variable,
// so they need to be dynamically allocated using the malloc() function,
// and deallocated using the free() function after use.

typedef struct node {
    char *artist ;
    char *songName ;
    char *genre ;
    struct node *nextNode ;
} Node;

// Declarations of linked list functions
//
// DECLARE YOUR LINKED-LIST FUNCTIONS HERE
//
Node *newNode(char songName[], char artist[], char genre[], Node *nextNode);
Node *scanAndInsertInOrder(char songName[], char artist[], char genre[], Node *head);
void printList(Node *head);
void printNode(Node *current);
void searchAndPrint(char songName[], Node*current);
void deleteNodeContents(Node*current);
Node *deleteAllNodes(Node *head);
Node *searchAndDelete(Node *head, char songName[]);

// Declarations of support functions
// See below the main function for descriptions of what these functions do

void inputStringFromUser( char prompt[], char s[], int arraySize ) ;
void songNameDuplicate( char songName[] ) ;
void songNameFound( char songName[] ) ;
void songNameNotFound( char songName[] ) ;
void songNameDeleted( char songName[] ) ;
void artistFound( char artist[] ) ;
void artistNotFound( char artist[] ) ;
void printMusicLibraryEmpty( void ) ;
void printMusicLibraryTitle( void ) ;

const int MAX_LENGTH = 1024;

int main( void ) {
    // Declare the head of the linked list.
    //   ADD YOUR STATEMENT(S) HERE
	Node *head = NULL;
	char artist[ MAX_LENGTH + 1];
	char songName[ MAX_LENGTH + 1];
	char genre[ MAX_LENGTH + 1];

    // Announce the start of the program
    printf("Personal Music Library.\n");
	printf("\nCommands are I (insert), D (delete), S (search by song name), P (print), Q (quit).\n");
	
	
    char response ;
    char input[ MAX_LENGTH + 1 ] ;
    do {
        inputStringFromUser( "\nCommand", input, MAX_LENGTH ) ;

        // Response is the first character entered by user.
        // Convert to uppercase to simplify later comparisons.
        response = toupper( input[0] ) ;

        if( response == 'I' ) {
            // Insert a song into the linked list.
            // Maintain the list in alphabetical order by song name.
            //   ADD STATEMENT(S) HERE
			inputStringFromUser( "Song name", songName, MAX_LENGTH ) ;
			inputStringFromUser( "Artist", artist, MAX_LENGTH ) ;
			inputStringFromUser( "Genre", genre, MAX_LENGTH ) ;
			
			head = scanAndInsertInOrder(songName, artist, genre, head);

            // USE THE FOLLOWING STRINGS WHEN PROMPTING FOR DATA:
            //    char *promptName = "Song name" ;
            //    char *promptArtist =  "Artist" ;
            //    char *promptGenre = "Genre" ;

        }
        else if( response == 'D' ) {
            // Delete a song from the list.

            char *prompt = "\nEnter the name of the song to be deleted" ;

            //   ADD STATEMENT(S) HERE
			inputStringFromUser( prompt, songName, MAX_LENGTH );
			
			head = searchAndDelete(head, songName);
        }
        else if( response == 'S' ) {
            // Search for a song by its name.

            char *prompt = "\nEnter the name of the song to search for" ;

            //   ADD STATEMENT(S) HERE
			inputStringFromUser( prompt, songName, MAX_LENGTH );
			
			searchAndPrint(songName, head);
        }
        else if( response == 'P' ) {
            // Print the music library.

            //   ADD STATEMENT(S) HERE
			printList(head);
        }
        else if( response == 'Q' ) {
            ; // do nothing, we'll catch this below
        }
        else {
            // do this if no command matched ...
            printf( "\nInvalid command.\n" ) ;
        }
    } while( response != 'Q' ) ;
  
    // Delete the entire linked list.
    //   ADD STATEMENT(S) HERE
	head = deleteAllNodes(head);

    // Print the linked list to confirm deletion.
    //   ADD STATEMENT(S) HERE
	printList(head);

    return 0 ;
}

// Support Function Definitions

// Prompt the user for a string safely, without buffer overflow
void inputStringFromUser(char prompt[], char s[], int maxStrLength) {
    int i = 0;
    char c;
    
    printf( "%s --> ", prompt ) ;
    while( i < maxStrLength && (c = getchar()) != '\n' )
        s[i++] = c ;
    s[i] = '\0' ;
}

// Function to call when the user is trying to insert a song name 
// that is already in the personal music library.
void songNameDuplicate( char songName[] ) {
    printf( "\nA song with the name '%s' is already in the music library.\n"
            "No new song entered.\n", songName);
}

// Function to call when a song name was found in the personal music library.
void songNameFound( char songName[] ) {
    printf( "\nThe song name '%s' was found in the music library.\n",
           songName ) ;
}

// Function to call when a song name was not found in the personal music library.
void songNameNotFound( char songName[] ) {
    printf( "\nThe song name '%s' was not found in the music library.\n",
           songName);
}

// Function to call when a song name that is to be deleted
// was found in the personal music library.
void songNameDeleted( char songName[] ) {
    printf( "\nDeleting a song with name '%s' from the music library.\n",
           songName);
}

// Function to call when printing an empty music library.
void printMusicLibraryEmpty(void) {
    printf( "\nThe music library is empty.\n" ) ;
}

// Function to call to print a title when the entire music library is printed.
void printMusicLibraryTitle(void) {
    printf( "\nMy Personal Music Library: \n" ) ;
}

// Add your functions below this line.

//   ADD STATEMENT(S) HERE
Node *newNode( char songName[], char artist[], char genre[], Node *nextNode) {
	Node *t = (Node *) malloc(sizeof(Node));
	
	if (t != NULL) {
		t -> songName = (char *) malloc(MAX_LENGTH * sizeof (char));
		t -> artist   = (char *) malloc(MAX_LENGTH * sizeof (char));
		t -> genre    = (char *) malloc(MAX_LENGTH * sizeof (char));
		
		strcpy(t -> songName, songName);
		strcpy(t -> artist, artist);
		strcpy(t -> genre, genre);
		
		t -> nextNode = nextNode;
	}
	
	return t;
}

//for Insertion
Node *scanAndInsertInOrder(char songName[], char artist[], char genre[], Node *head) {
	//special cases, if empty list of song should be first of the list
	if (head == NULL || strcmp(head -> songName, songName) > 0) {
		return newNode(songName, artist, genre, head);
	} else {
		Node *current = head;
		
		//gets to the node before where it should be placed
		while (current -> nextNode != NULL && strcmp(current -> nextNode -> songName, songName) <= 0) {
			current = current -> nextNode;
		}
		
		//checks if there is duplicate, returning error if there is
		if (strcmp(current -> songName, songName) == 0) {
			songNameDuplicate(songName);
			return head;
		}
		
		//adds node in order
		current -> nextNode = newNode(songName, artist, genre, current -> nextNode);
		return head;
	}
	
}

void printList(Node *head) {
	Node *current = head;
	
	//checks for empty library, and prints title after for non-empty
	if (current == NULL) {
		printMusicLibraryEmpty();
		return;
	} else {
		printMusicLibraryTitle();
	}
	
	//prints node, moves to next node
	while (current != NULL) {
		printNode(current);
		
		current = current -> nextNode;
	}
}

//prints the contents of the node
void printNode(Node *current) {
		printf("\n%s\n", current -> songName);
		printf("%s\n", current -> artist);
		printf("%s\n", current -> genre);
}

void searchAndPrint(char songName[], Node*current) {
	//checks the each node, if list is empty this block is skipped
	while (current != NULL) {
		if(strcmp(current -> songName, songName) == 0){
			songNameFound(songName);
			printNode(current);
			return;
		}
		current = current -> nextNode;
	} 
	
	//if it didnt returnt already, wasn't found
	songNameNotFound(songName);
}

void deleteNodeContents(Node*current) {
	songNameDeleted(current -> songName);
	
	free (current -> songName);
	free (current -> artist);
	free (current -> genre);
}

Node *deleteAllNodes(Node *head) {
	//runs through each node, deletes contents frist and then node
	while (head != NULL) {
		deleteNodeContents(head);
		Node *firstNode = head;
		head = head -> nextNode;
		free(firstNode);
	}
	return NULL;
}


Node *searchAndDelete(Node *head, char songName[]) {
  bool found = false;
  
	//handles the special case first where the node to delete is head
   while (head != NULL && strcmp(head -> songName, songName) == 0) {
    Node *firstNode = head;
    head = head -> nextNode;
	deleteNodeContents(firstNode);
    free(firstNode);
	found = true;
  }

  if (head != NULL) {
    Node *current = head;
	//looks at the next node, if it is to be deleted, will delete and make the node after the next node
    while (current -> nextNode != NULL) {
      if (strcmp(current -> nextNode -> songName, songName) == 0) {
        Node *nodeToRemove = current -> nextNode;
        current -> nextNode = current -> nextNode -> nextNode;
		deleteNodeContents(nodeToRemove);
        free(nodeToRemove);
		found = true;
      }
      else // only advance 'current' if nothing is deleted
        current = current -> nextNode;
    }
  }
  
  if(!found) {
	  songNameNotFound(songName);
  }
  
  return head;
}