#pragma once

#ifndef Hand_h
#define Hand_h

#include "stdafx.h"
#include <string>
#include "Deck.h"
#include <memory>
#include <list>

using namespace std;


class Hand {
private:
	vector<Card> cards;

public:
	Hand_Type ht = NO_RANK;
	Hand();
	Hand(const Hand &h);

	//destructor

	Hand& Hand::operator=(const Hand& h);
	vector<Card> Hand::operator+(const Hand&h);
	bool Hand::operator==(Hand &h);
	bool Hand::operator<(const Hand &h);
	Card Hand::operator[](size_t index);
	Card remove_card(size_t index);
	void sortHand();
	string Hand::hiddenView();


	unsigned int Hand::size();

	string asString() const;

	friend void operator<<(ostream &os, Hand &h);
	friend void operator<<(Hand &h, Deck &d);
	friend void operator<<(Deck &d, Hand &h);
	friend void operator<<(Hand &h, Card c);
	friend bool poker_rank(const Hand &h1, const Hand &h2);
	friend int findCLocation(const Hand &h);
	friend vector<Card> arrange2PairHand(const Hand &h);
	friend int getPairLocation(const Hand &h);
	friend vector<Card> arrangePairHand(const Hand &h);
	friend int findUnmatchedThreeOfKind(const Hand &h);
	friend vector<Card> arrangeThreeKind(const Hand &h);
	friend vector<Card> arrangeFullHouse(const Hand &h);
	friend vector<Card> arrangeFourKind(const Hand &h);
	friend vector<Card> arrangeStraight(const Hand &h);
	friend vector<Card> arrangeFlush(const Hand &h);
	friend vector<Card> arrangeHand(Hand &h);

};

void operator<<(ostream &os, Hand &h);
void operator<<(Hand &h, Deck &d);
void operator<<(Hand &h, Card c);
void operator<<(Deck &d, Hand &h);

int getPairLocation(const Hand &h);
vector<Card> arrangePairHand(const Hand &h);

int findCLocation(const Hand &h);
vector<Card> arrange2PairHand(const Hand &h);

bool poker_rank(const Hand &h1, const Hand &h2);

int findUnmatchedThreeOfKind(const Hand &h);
vector<Card> arrangeThreeKind(const Hand &h);
vector<Card> arrangeFullHouse(const Hand &h);
vector<Card> arrangeFourKind(const Hand &h);
vector<Card> arrangeStraight(const Hand &h);
vector<Card> arrangeFlush(const Hand &h);
vector<Card> arrangeHand(Hand &h);

Hand parse_hand(list<string> cardDefs);


#endif /* Hand_h */