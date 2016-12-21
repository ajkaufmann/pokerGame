#pragma once

#ifndef Deck_h
#define Deck_h

#include "stdafx.h"
#include "Parsing.h"

using namespace std;

class Deck {
private:
	vector<Card> cards;
	Deck &operator=(Deck &d);

public:
	Deck(string filename);

	Deck();

	//destructor is fine

	void load(string filename);

	int shuffle();

	unsigned int size() const;

	vector<Card>& getCards();

	friend void operator<<(ostream &os, Deck &d);

	void addCard(Card c);

	Card dealCard();
	friend void operator<<(Deck &d1, Deck &d2);
};

void operator<<(ostream &os, const Deck &d);
void operator<<(Deck &d1, Deck &d2);


#endif /* Deck_h */