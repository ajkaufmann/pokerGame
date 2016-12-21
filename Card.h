#pragma once

#include "stdafx.h"
#include <algorithm>
#include <string>
#include <vector>

#ifndef Card_h
#define Card_h

using namespace std;

enum Suit { INVALID_SUIT = -1, HEART = 1, CLUB = 2, DIAMOND = 3, SPADE = 4 };
enum Rank { INVALID_RANK = -1, TWO = 2, THREE = 3, FOUR = 4, FIVE = 5, SIX = 6, SEVEN = 7, EIGHT = 8, NINE = 9, TEN = 10, JACK = 11, QUEEN = 12, KING = 13, ACE = 14 };
enum Hand_Type { FOLDED, NO_RANK, PAIR_HAND, TWO_PAIR, THREE_OF_KIND, STRAIGHT, FLUSH_HAND, FULL_HOUSE, FOUR_OF_KIND, STRAIGHT_FLUSH };

struct Card {
	Suit cardSuit;
	Rank cardRank;
	bool facedown;
	bool operator<(const Card & card2) const;
	bool Card::operator==(const Card &ct) const;
	Card(Rank r, Suit s);
	Card(Rank r, Suit s, bool f);
	Card();
};

string getRankString(Rank r);

string getSuitString(Suit s);

string cardToString(Card curCard);

int getRankVal(Rank r);

int printCards(const vector<Card> & cards);

string handTypeToString(Hand_Type h);

bool same_suit(const Card &c1, const Card &c2);

#endif /* Card_h */