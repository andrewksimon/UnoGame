#define  _SCL_SECURE_NO_WARNINGS


//
// UnoPlayer.cpp
//
// This is the UnoPlayer.cpp function of the UnoGame program. 
// This program was made by Andrew Simon.
// This program was made on 01/12/2016.
// This program was last modified on 07/12/2016.


//Preprocessor Directeives
#pragma once
#include <iostream>
#include <string>
using namespace std;

#include "OrderedList.h"
#include "UnoCard.h"


//This one is pretty simple.
//A player holds a hand as well as a some sort of ID.


//Define the class for the Uno Player
class UnoPlayer {

private:
	//Creates an ordered list to hold the players' cards.
	//SHOULD HAVE SIZED DEFINED?? - Don't worry about it - size = 200. 
	OrderedList<UnoCard> m_PlayerHand;
	//Holds the ID of the current player.
	int m_playerID;

public:
	//Default constrctor
	//Override for number of cards.
	UnoPlayer(int PlayerID = 0);
	//Default destructor.
	~UnoPlayer();

	//Functions that deal with the player's Hand.
	void addCardToPlayerHand(UnoCard addCard);
	//bool removeCardfromPlayerHand(UnoCard removeCard);
	//bool lookForMatchInPlayerHand(UnoCard lookupCard);

	//Handels diffrent cases.
	int lookForASuitIndex(UnoCard lookupCard);
	int lookForADenominationIndex(UnoCard lookupCard);
	UnoCard returnCard(int index);
	UnoCard UnoPlayer::viewCard(int index);
	int uno();
	int getID();
	void printHand();

};

//Uno Player custom number of cards in hand constructor.
UnoPlayer::UnoPlayer(int playerID) {

	//Assign the current player ID.
	m_playerID = playerID;


}

//The Default Destructor
UnoPlayer :: ~UnoPlayer() {

	//Does nothing until the program ends.

}

//Adds a card to the player's hand.
void UnoPlayer::addCardToPlayerHand(UnoCard addCard) {

	//Calls the insert function from the Orderd List.
	m_PlayerHand.insert(addCard);

}

//Not needed, but is kept just in case. The event that an identical card
//is to be found in the deck is so unlikely, that checking for it is a waste
//of system resources.
/*

//Removes a card from the player's hand.
//NOT NEEDED
bool UnoPlayer::removeCardfromPlayerHand(UnoCard removeCard) {

	//Calls the remove function from the Orderd List.
	//Does a quick binary search for the index of the card we want to remove.
	int index = m_PlayerHand.binarySearch(removeCard);

	//If the card is not there, the fxn will return -1.
	if (index == -1) {
		//Return a false to state the card could NOT be removed.
		return false;
	}
	else {
		//Remove the card from the ordered list.
		m_PlayerHand.remove(index);
		//Return a true to state the card WAS found.
		return true;
	}

}

//Looks for a matching card within the player's hand.
//NOT NEEDED
bool UnoPlayer::lookForMatchInPlayerHand(UnoCard lookupCard) {

	//Calls the Binary Search function from the Ordered List.
	//Checks to see if the card exisits.
	if (m_PlayerHand.binarySearch(lookupCard) == -1) {
		//Return false to indicate the card could not be found.
		return false;
	}
	else {
		//Retun a true to indicate the card WAS found.
		return true;
	}


}

*/

//Looks for the index of the First matching suit in the player's hand.
int UnoPlayer::lookForASuitIndex(UnoCard lookupCard) {

	//Index through the player's hand.
	for (int i = 1; i <= m_PlayerHand.getLength(); i++) {
		//Look for a suit matching at an index in the player's hand.
		if (m_PlayerHand.retrieve(i).getSuit() == lookupCard.getSuit()) {
			//Return the FIRST index it was found at.
			return i;
		}
	}

	//No matching suit was found in the player's hand.
	return -1;

}

//Looks for the index of the First matching denom in the player's hand.
int UnoPlayer::lookForADenominationIndex(UnoCard lookupCard) {

	//Index through the player's hand.
	for (int i = 1; i <= m_PlayerHand.getLength(); i++) {
		//Look for a suit matching at an index in the player's hand.
		if (m_PlayerHand.retrieve(i).getDenomination() == lookupCard.getDenomination()) {
			//Return the FIRST index it was found at.
			return i;
		}
	}

	//No matching suit was found in the player's hand.
	return -1;

}

//Views a card at the given index of the player's hand. It's like returnCard, but the card does not get removed
//from the players hand.
UnoCard UnoPlayer::viewCard(int index) {
	/*
	We've already checked to see if this suit exsists in the player's hand.
	This was checked with lookForASuit(UnoCard lookupCard) or the lookForADenomination(UnoCard lookupCard)
	functions. If the error check of -1 is passed, the user may request the card at that index maybe be viewed
	and returned as another card.
	*/

	//Remove and view that card from the player's hand.
	//INDEX CANNOT = -1.
	return m_PlayerHand.retrieve(index);

}

//Removes and returns the card from the matching index within the player's hand.
UnoCard UnoPlayer::returnCard(int index) {
	/*
	We've already checked to see if this suit exsists in the player's hand.
	This was checked with lookForASuit(UnoCard lookupCard) or the lookForADenomination(UnoCard lookupCard)
	functions. If the error check of -1 is passed, the user may request the card at that index maybe be removed
	and returned.
	*/

	//Remove and return that card from the player's hand.
	//INDEX CANNOT = -1.
	return m_PlayerHand.remove(index);

}

//Shows the card from the matching index within the player's hand.
void UnoPlayer::printHand() {

	//Print out all the cards that are in the player's hand.
	for (int i = 1; i <= m_PlayerHand.getLength(); i++) {
		cout << m_PlayerHand.retrieve(i) << endl;
	}

}

//Returns a int stating if our player has one card left.
//Return 0 for win, 1 for uno and 2 for more than one card.
int UnoPlayer::uno() {

	//If the player has one card in their hand, return 1
	if (m_PlayerHand.getLength() == 1) {
		return 1;
		//If the player has no more cards, return 0;
	}
	else if (m_PlayerHand.getLength() == 0) {
		return 0;
	}
	else {
		//If the player has more than one card, return 2.
		return 2;
	}

}

//Returns the player's ID.
int UnoPlayer::getID() {

	return m_playerID;

}