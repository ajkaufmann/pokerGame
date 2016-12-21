#include "stdafx.h"
#include "Card.h"
#include <iostream>

using namespace std;

Card::Card(Rank r, Suit s) {
	cardRank = r;
	cardSuit = s;
	facedown = false;
}

Card::Card(Rank r, Suit s, bool f) {
	cardRank = r;
	cardSuit = s;
	facedown = f;
}

Card::Card()
{
	cardRank = INVALID_RANK;
	cardSuit = INVALID_SUIT;
	facedown = true;
}

string getRankString(Rank r) {
	switch (r) {
	case ACE: return "ace";
	case TWO: return "two";
	case THREE: return "three";
	case FOUR: return "four";
	case FIVE: return "five";
	case SIX: return "six";
	case SEVEN: return "seven";
	case EIGHT: return "eight";
	case NINE: return "nine";
	case TEN: return "ten";
	case JACK: return "jack";
	case QUEEN: return "queen";
	case KING: return "king";
	default: return "Bad card rank";
	}
}

string getSuitString(Suit s) {
	switch (s) {
	case HEART: return "Heart";
	case DIAMOND: return "Diamond";
	case SPADE: return "Spade";
	case CLUB: return "Club";
	default: return "Bad suit rank";
	}
}

string cardToString(Card curcard) {
	string outputstring = "";
	outputstring = outputstring + getRankString(curcard.cardRank);
	outputstring = outputstring + " of ";
	outputstring = outputstring + getSuitString(curcard.cardSuit);
	outputstring = outputstring + "s";
	return outputstring;
}

int getRankVal(Rank r) {
	switch (r) {
	case ACE: return 14;
	case TWO: return 2;
	case THREE: return 3;
	case FOUR: return 4;
	case FIVE: return 5;
	case SIX: return 6;
	case SEVEN: return 7;
	case EIGHT: return 8;
	case NINE: return 9;
	case TEN: return 10;
	case JACK: return 11;
	case QUEEN: return 12;
	case KING: return 13;
	default: return 0;
	}
}

int printCards(const vector<Card> & cards) {
	for (unsigned int i = 0; i < cards.size(); ++i) {
		string str = cardToString(cards[i]);
		cout << str << endl;
	}
	return 0;
}

string handTypeToString(Hand_Type h) {
	switch (h)
	{
	case FOLDED:
		return "Folded.";
			break;
	case NO_RANK:
		return "No Rank, High Card";
		break;
	case PAIR_HAND:
		return "1 Pair";
		break;
	case TWO_PAIR:
		return "2 Pair";
		break;
	case THREE_OF_KIND:
		return "Three of a kind";
		break;
	case STRAIGHT:
		return "Straight";
		break;
	case FLUSH_HAND:
		return "Flush";
		break;
	case FULL_HOUSE:
		return "Full House";
		break;
	case FOUR_OF_KIND:
		return "Four of a Kind";
		break;
	case STRAIGHT_FLUSH:
		return "Straight Flush";
		break;
	default:
		return "Invalid Hand";
		break;
	}
}

bool Card::operator<(const Card &card2) const {
	if (cardRank == card2.cardRank) {
		return cardSuit < card2.cardSuit;
	}
	return cardRank < card2.cardRank;
}

bool same_suit(const Card & c1, const Card & c2)
{
	Suit s1 = c1.cardSuit;
	Suit s2 = c2.cardSuit;
	return s1 < s2;
}