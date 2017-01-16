#define  _SCL_SECURE_NO_WARNINGS
#pragma once

//
// UnoGame.cpp
//
// This is the UnoCard.cpp function of the UnoGame program. 
// This program was made by Andrew Simon.
// This program was made on 01/12/2016.
// This program was last modified on 07/12/2016.

#include <stdlib.h>
#include <time.h>
//For pasuing in milliseconds.
#include <windows.h>

#include <iostream>
//#include <string.h>
using namespace std;

//Include the data structures.
#include "CircularDoublyLinkedList.h"
#include "Bag.h"
#include "Stack.h"
#include "Queue.h"
//Include the game files.
#include "UnoPlayer.h"
#include "UnoCard.h"

//This is the actual game mechanic.
//This will be adding the players to a CDLL in order to circle through them.

//Class definition.
class UnoGame {

private:
	//1. Instantiate the players based on the number of players using a CDLL.
	CDLinkedList<UnoPlayer*> UnoGamePlayers;

	//2. Creates a Stack to hold the Discard pile.
	Stack<UnoCard> DiscardPile;
	//Overloaded later on.

	//3. Creates a bag to hold the cards.
	Bag<UnoCard> DeckOfCards;
	//Overloaded later on.

	//4. Create a Queue to hold the draw pile.
	Queue<UnoCard> DrawPile;


public:

	//Default constrctor with default overloads.
	//Sets up the game.
	UnoGame(int NumberOfPlayers = 3, int NumberOfCardsInHand = 7, int sizeOfDeck = 40, int rankSize = 5);
	//Default destructor
	~UnoGame();

	//Game Specific functions.
	void runtime(unsigned int milisec);
	void printGame(int index);
	void shuffleDeck();

};

//Default Constructor for the Uno Game.
//Essentially sets up the entire game.
UnoGame::UnoGame(int NumberOfPlayers, int NumberOfCardsInHand, int sizeOfDeck, int rankSize) : DeckOfCards(sizeOfDeck), DiscardPile(sizeOfDeck) {

	//Definition arrays to create the deck of cards...
	Suit su[] = { RED, GREEN, BLUE, YELLOW };
	Denomination de[] = { N1, N2, N3, N4, N5, N6, N7, N8, N9 };

	//Seed random.
	srand((unsigned)time(NULL));

	//Instantiate the players based on the number of players using a CDLL.
	//UnoPlayer* temp = new UnoPlayer(1);
	UnoGamePlayers.addHead(new UnoPlayer(1));
	for (int i = 1; i < NumberOfPlayers; i++) {
		UnoGamePlayers.addTail(new UnoPlayer(i + 1));
	}


	//Make the deck of cards and throw them into the bag.
	//Iterates throught the colour cards until the the deck size requirement is met.
	int tempDeck = sizeOfDeck;
	
	while (tempDeck){

		for (int x = 0; x < 4 && tempDeck != 0; x++) {
			//Iterates through the number cards.
			for (int y = 0; y < rankSize && tempDeck != 0; y++) {
				//Add that card to the bag.
				DeckOfCards.add(UnoCard(su[x], de[y]));
				tempDeck--;
			}
		}
	}


	//Assign the players the set number of cards in hand.
	for (int i = 1; i <= NumberOfPlayers; i++) {
		for (int j = 0; j < NumberOfCardsInHand; j++) {
			//I don't know why this does not work.
			UnoGamePlayers.retrieve(i)->addCardToPlayerHand(DeckOfCards.getOne());
		}
	}


	//Move the remainder of the cards to the Queue, or the Draw Pile.
	while (!DeckOfCards.isEmpty()) {
		//UnoCard temp = DeckOfCards.getOne;
		//DrawPile.enqueue(temp);
		//GONNA BE RANDOM.
		DrawPile.enqueue(DeckOfCards.getOne());
	}


	//Adds 1 card to the top of the discard pile for the refence card.
	DiscardPile.push(DrawPile.dequeue());


}

//The default destructor.
UnoGame :: ~UnoGame() {

	//NEEDED
	//Deletes the Player Pointers.
	while (UnoGamePlayers.size() != 0) {
		delete UnoGamePlayers.removeTail();
	}

}

//Calling this will start the game's AI running.
void UnoGame::runtime(unsigned int milisec) {

	//LET THE GAMES BEGIN~!
	//Start the Simulation!
	//Here is where we code the AI.

	

	//Displays all the players hands before the game. This is just so the user can see.
	for (int i = 1; i <= UnoGamePlayers.size(); i++) {
		printGame(1);
		cout << "Lets see all the player's hands. This is currently Player " << UnoGamePlayers.retrieveHead()->getID() << "'s Hand." << endl << endl;
		UnoGamePlayers.shift(0);
		//system("PAUSE");
		if (milisec != 0) {
			Sleep(milisec);
		} else {
			system("PAUSE");
		}
	}

	//Has anyone run?
	bool win = false;

	//Keep going while there is no winner.
	while (win == false) {

		//These temp values are here to make coding easier.
		//Lets just get the head each time.
		//UnoPlayer* tempPlayer = UnoGamePlayers.retrieveHead();

		//Player checks the top of the discard pile. "PEEK" at stack.
		UnoCard topDiscard = DiscardPile.peek();

		//Print 2/3 of the board
		printGame(1);

		/*
		//Checks for an exact card match???
		//if (tempPlayer->removeCardfromPlayerHand(topDiscard) == true) {
		//	//Take the card from the player and put it in the pile.
		//	DiscardPile.push(topDiscard);
		//	//Print out that exact card value was found.
		//	cout << "Player " << tempPlayer->getID() << " has an exact matching card of " << topDiscard.stringCard() << endl;
		//} else {
		//	cout << "Player " << tempPlayer->getID() << " has an exact matching card of " << topDiscard.stringCard() << endl;
		//}
		*/

		//If there is no EXACT match, look for an denomination or suit.
		int denomIndex = UnoGamePlayers.retrieveHead()->lookForADenominationIndex(topDiscard);
		int suitIndex = UnoGamePlayers.retrieveHead()->lookForASuitIndex(topDiscard);

		
		//Check the number for a match.
		if (denomIndex != -1) {
			//If found, take the card out of the player's hand. //topDiscard
			cout << " - Player " << UnoGamePlayers.retrieveHead()->getID() << " has a matching Denomination with card " << UnoGamePlayers.retrieveHead()->viewCard(denomIndex) << "." << endl << endl;
			DiscardPile.push(UnoGamePlayers.retrieveHead()->returnCard(denomIndex));
			
		}
		//Check for a colour match.
		else if (suitIndex != -1) {
			//If found, take the card out of the player's hand. //topDiscard
			cout << " - Player " << UnoGamePlayers.retrieveHead()->getID() << " has a matching Colour with card " << UnoGamePlayers.retrieveHead()->viewCard(suitIndex) << "." << endl << endl;
			DiscardPile.push(UnoGamePlayers.retrieveHead()->returnCard(suitIndex));

		//If no match is found, have the player pick up a card.
		} else {

			cout << " - Player " << UnoGamePlayers.retrieveHead()->getID() << " has NO common card. Draw one... " << endl << endl;
			
			//Pull one card from the draw pile if the draw pile is not empty.
			if (DrawPile.isEmpty() == false) {

				UnoCard tempCard = DrawPile.dequeue();
				UnoGamePlayers.retrieveHead()->addCardToPlayerHand(tempCard);
				cout << " - Player " << UnoGamePlayers.retrieveHead()->getID() << " has picked up " << tempCard << "." << endl << endl;

				//Reprint the deck to reflect the change.
				//system("PAUSE");
				//printGame(1);

			//WHAT IF WE RUN OUT OF CARDS?
			//If the draw pile is empty, call shuffle.
			} else if (DrawPile.isEmpty() == true) {
				//Call shuffle to repopulate the DrawPile...
				cout << " - No more cards left in the draw deck... Shuffling discard pile." << endl << endl;
				shuffleDeck();
				//Pull one card from the draw pile
				cout << " - Player " << UnoGamePlayers.retrieveHead()->getID() << " has NO common card. Draw one... " << endl << endl << endl;
				UnoCard tempCard = DrawPile.dequeue();
				UnoGamePlayers.retrieveHead()->addCardToPlayerHand(tempCard);
				cout << " - Player " << UnoGamePlayers.retrieveHead()->getID() << " has picked up " << tempCard << "." << endl << endl << endl;

				//Reprint the deck to reflect the change.
				//system("PAUSE");
				//printGame(1);

			}

		}


		//DETERMINES IF THERE IS A WIN.
		//Checks for an Uno or a win.
		if (UnoGamePlayers.retrieveHead()->uno() == 0) {
			cout << " - Player " << UnoGamePlayers.retrieveHead()->getID() << " has WON this round of UNO!" << endl << endl;
			//Print out that this player has won.
			win = true;
			//Pause the game until the user hits enter.
			//system("pause");
			if (milisec != 0) {
				Sleep(milisec);
			} else {
				system("PAUSE");
			}

			//If the player still has 1 card or more, keep playing.
		} else if (UnoGamePlayers.retrieveHead()->uno() == 1) {
			//The player has not won the round, but has one card left in their hand.
			cout << " - Player " << UnoGamePlayers.retrieveHead()->getID() << " has called UNO!" << endl << endl;


			//ADDED TO FIX UNO CARD CALLER PLAYING TWICE IN THE SAME ROUND.
			//Reprint the deck to reflect the change.
			//system("PAUSE");
			if (milisec != 0) {
				Sleep(milisec);
			} else {
				system("PAUSE");
			}
			printGame(1);

			//Players don't move around, the CDLL does!
			//Shift left by one.
			UnoGamePlayers.shift(0);
			//Repete until winner is found or cards are gone.
			cout << " - It is now Player " << UnoGamePlayers.retrieveHead()->getID() << "'s turn!" << endl << endl;
			//Pause the game until the user hits enter.
			//system("pause");
			if (milisec != 0) {
				Sleep(milisec);
			} else {
				system("PAUSE");
			}

		} else {

			//Reprint the deck to reflect the change.
			//system("PAUSE");
			if (milisec != 0) {
				Sleep(milisec);
			} else {
				system("PAUSE");
			}
			printGame(1);

			//Players don't move around, the CDLL does!
			//Shift left by one.
			UnoGamePlayers.shift(0);
			//Repete until winner is found or cards are gone.
			cout << " - It is now Player " << UnoGamePlayers.retrieveHead()->getID() << "'s turn!" << endl << endl;
			//Pause the game until the user hits enter.
			//system("pause");
			if (milisec != 0) {
				Sleep(milisec);
			} else {
				system("PAUSE");
			}
		}
		



		cout << endl;
		
		
	}

}

//This function empties the discard pile except for the top card,
//and adds shuffles them, then places them back to the Draw deck.
void UnoGame::shuffleDeck() {

	//put cards back in bag, then to deck

	//Before we move the contents, we're going to have to save the top element.
	//This is because this card is used as a reference. 
	UnoCard topCard = DiscardPile.pop();


	//Move all the remaining contents of the Queue to the bag. 
	//ISSUE seems to be here.
	while (DiscardPile.isEmpty() == false) {
		UnoCard temp = DiscardPile.pop();
		DeckOfCards.add(temp);
	}

	//Place the top card back into the discard stack.
	DiscardPile.push(topCard);

	//Put the rest of the cards back into the draw pile.
	while (DeckOfCards.isEmpty() == false) {
		DrawPile.enqueue(DeckOfCards.getOne());
	}

}

//This function prints out the entire game.
void UnoGame::printGame(int index) {


	switch (index) {

		//Print the top section
		case 1:

			//Clear the Screen first...
			system("cls");
			//Print the values.
			cout
				<< "================== UNO ===================" << endl
				<< endl

				//Print the card piles avaliable.
				<< "Draw Pile Size:			" << DrawPile.size() << endl
				<< "Discard Pile Size:		" << DiscardPile.size() << endl
				<< "Last Played Card/Top Discard:	" << DiscardPile.peek() << endl
				<< endl

				<< endl
				//Prints out the current player.
				<< "Who's turn is it?: Player " << UnoGamePlayers.retrieveHead()->getID() << endl
				<< endl

				//Print out the player's current hand.
				<< endl
				<< "Player " << UnoGamePlayers.retrieveHead()->getID() << "'s current hand: " << endl
				<< "====================" << endl;
			//Call the card print function.
			UnoGamePlayers.retrieveHead()->printHand();
			//Prints out the current status.
			cout 
				<< endl
				<< "Current Status:" << endl
				<< "====================" << endl
				<< endl;
				
			break;

		case 2:

			//Nothing in here.
			//Was intended for a scondary print.
			
			break;

	}

}
