//
// This is the main.cpp function of the UnoGame program. 
//
//
// This program was made by Andrew Simon.
// This program was made on 01/12/2016.
// This program was last modified on 07/12/2016.

//Preprocessor directives
#include <iostream>
using namespace std;

#include "UnoGame.h"


void main() {

	//Temporary variables to hold the paramaters for the game instance. 
	bool valid = false;
	int players = 3;
	int handSize = 7;
	//DECK SIZE is OVERWRITTEN automatically below to ensure that enough cards are present.
	//To have a custom deck, please modifie the code below as well.
	int deckSize = 0;
	int rankSize = 5;
	unsigned int time = 0;

	//Keep looping until a valid input is found.
	while (!valid) {

		//Prints out a welcome message.
		cout
			<< "================ Welcome to UNO! ================" << endl
			<< endl
			<< endl;

		//Asks for the number of AIs in the game.
		cout
			<< "Please enter the number of CPU Players (for default, enter 3): ";
		cin >> players;


		//Asks for the hand size.
		cout
			<< endl << endl
			<< "Please enter the hand size (for default, enter 7): ";
		cin >> handSize;

		////Asks for the size of the deck.
		//cout
		//	<< endl << endl
		//	<< "Please enter the deck size (for default, enter 50): ";
		//cin >> deckSize;

		//Asks for the number of denominations.
		cout
			<< endl << endl
			<< "Please enter the denomination size (for default number cards 1 to 5, enter 5): ";
		cin >> rankSize;


		//Asks if the game should run automatically.
		cout
			<< endl << endl
			<< "Do you want to signal each step (enter 0) or have the game step through every 1 second (enter 1000)?: ";
		cin >> time;


		cout << endl << endl;

		//Does some basic error checking...

		//Makes sure that the cards in hand(s) do not excced deck size.
		if (deckSize < (players*handSize)+10) {
			valid = false;
			cout
				<< "ERROR! Cards required excceed deck size!" << endl
				<< endl
				<< "Number of Players:		" << players << endl
				<< "Size of Hand:			" << handSize << endl
				<< "Reccomended Deck Size:	" << (players*handSize) + 10 << endl
				<< "*** The reccomended deck size is based on the player hand times the hand size plus 10 extra draw cards. ***" << endl
				<< "Please enter these values again. Press enter to succeed..." << endl;
			
		} else {
			valid = true;
		}

		system("PAUSE");
		system("cls");

	}


	
	//Breif override of the Deck size. We want to ensure that the deck size is large enough.
	deckSize = (players*handSize) + 15;


	//Starts the game call.
	UnoGame newGame(players, handSize, deckSize, rankSize);

	//Start the game.
	newGame.runtime(time);

	system("pause");


}



