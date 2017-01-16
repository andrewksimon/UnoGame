#define  _SCL_SECURE_NO_WARNINGS

//
// UnoCard.cpp
//
// This is the UnoCard.cpp function of the UnoGame program. 
// This program was made by Andrew Simon.
// This program was made on 01/12/2016.
// This program was last modified on 07/12/2016.


//Preprocessor Directeives
#pragma once
#include <iostream>
#include <string>
using namespace std;


// User defined Suit and Denomination types (user-defined integers) 
enum Suit { RED = 1, GREEN = 2, BLUE = 3, YELLOW = 4 };
enum Denomination { N1 = 1, N2 = 2, N3 = 3, N4 = 4, N5 = 5, N6 = 6, N7 = 7, N8 = 8, N9 = 9 };

//This is essentially the "Header", where all of the functions are outlined. 
class UnoCard {

public:
	//Constructor with some Default values.
	UnoCard(Suit suit = RED, Denomination denomination = N1);
	//Default Destructor
	~UnoCard();

	//Removed the "inline" thing from Suit and Denomination.
	inline Suit getSuit(void) const { return m_suit; }
	inline Denomination getDenomination(void) const { return m_denomination; }
	char toCharSuit(void); // Returns a char that "describes" card's suit
	char toCharDenomination(void); // returns a char that "describes" card's denomination
	//string stringCard();


private:
	Suit m_suit; // Private storage of suit
	Denomination m_denomination; // Private storage of denomination
								 //Print function override.
	friend std::ostream& operator<<(std::ostream& os, const UnoCard &c);
};

// global operator functions comparing denominations of two cards
// The cards a and b are passed by reference
inline bool operator<(const UnoCard& a, const UnoCard& b) {
	if (a.getSuit() == b.getSuit()) return (a.getDenomination()<b.getDenomination());
	else                            return (a.getSuit()<b.getSuit());
}
inline bool operator>(const UnoCard& a, const UnoCard& b) {
	if (a.getSuit() == b.getSuit()) return (a.getDenomination()>b.getDenomination());
	else                            return (a.getSuit()>b.getSuit());
}
// checks equality of suits and denominations for two cards
inline bool operator==(UnoCard& a, UnoCard& b) { return (a.getDenomination() == b.getDenomination() && a.getSuit() == b.getSuit()); }

//Default card construtor.
UnoCard::UnoCard(Suit suit, Denomination denomination) : m_suit(suit), m_denomination(denomination) {

	//Define the card.

}

//Default destructor
UnoCard :: ~UnoCard() {
	//Do Nothing until the program exits.
}

//Parses the suit name to a String.
char UnoCard::toCharSuit() {
	if (m_suit == RED)   return 'R';
	else if (m_suit == GREEN)    return 'G';
	else if (m_suit == BLUE)   return 'B';
	else return 'Y';
}

//Parses the the denomination to a Char
char UnoCard::toCharDenomination() {

	if (m_denomination == N1)	return '1';
	else if (m_denomination == N2)	return '2';
	else if (m_denomination == N3)	return '3';
	else if (m_denomination == N4)	return '4';
	else if (m_denomination == N5)	return '5';
	else if (m_denomination == N6)	return '6';
	else if (m_denomination == N7)	return '7';
	else if (m_denomination == N8)	return '8';
	else return '9';

}

//cout overload function.
std::ostream & operator<<(std::ostream& os, const UnoCard &c) {

	int suit = c.getSuit();
	int demo = c.getDenomination();

	//Print Demo
	os << demo;

	//Print Suit
	switch (suit) {
	case 1:
		os << " - Red";
		break;
	case 2:
		os << " - Green";
		break;
	case 3:
		os << " - Blue";
		break;
	default:
		os << " - Yellow";
	}

	return os;
}


//Custom string parser. This is used if I wanted to parse the card to a string rather than using cout.
//Commented out because it does work, but not needed.
/*
string UnoCard::stringCard() {

	int suit = m_suit;
	int demo = m_denomination;

	string temp;

	//Print Demo
	temp += demo;

	//Print Suit
	switch (suit) {
	case 1:
		temp += " - Red";
		break;
	case 2:
		temp += " - Green";
		break;
	case 3:
		temp += " - Blue";
		break;
	default:
		temp += " - Yellow";
	}

	return temp;
	
}

*/