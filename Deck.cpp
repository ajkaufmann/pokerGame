#include "stdafx.h"
#include "Deck.h"
#include <random>
#include <iterator>

using namespace std;

Deck::Deck(string filename)
{
	try
	{
		Deck::load(filename);
	}
	catch (Error_Values ev)
	{
		Deck();
		throw ev;
	}

}

Deck::Deck() {}

void Deck::load(string filename)
{
	ifstream ifs(filename);
	string line;
	int numCards = 0;
	if (ifs.is_open()) {
		while (getline(ifs, line)) {
			istringstream iss(line);
			string singledef;
			auto goToNewLine = false;
			while (iss >> singledef && !goToNewLine) {
				if (isPosCardDef(singledef)) {
					goToNewLine = foundComment(singledef);
					if (!goToNewLine) {
						Card newcard = stringToCard(singledef);
						if (isValidCard(newcard)) {
							cards.push_back(newcard);
						}
					}
					else {
						break;
					}
				}
				if (singledef.size() >= 4 && singledef[3] == '/') { //this checks if the singledef ends in a comment meaning shouldn't read the rest of the line
					goToNewLine = true;
				}
			}
		}
		ifs.close();
	}
	else {
		throw FILE_FAILED_TO_OPEN;
	}
}

int Deck::shuffle()
{
	default_random_engine engine(std::random_device{}());
	std::shuffle(cards.begin(), cards.end(), engine);
	return NO_ERROR;
}

unsigned int Deck::size() const
{
	return cards.size();
}

vector<Card>& Deck::getCards() {
	return cards;
}

void Deck::addCard(Card c)
{
	cards.push_back(c);
}

//check if this is the right way to do it?
Card Deck::dealCard()
{
	if (cards.size() <= 0) {
		throw NOT_ENOUGH_CARDS;
		return Card();
	}
	Card c = cards[cards.size() - 1];
	cards.pop_back();
	return c;
}

void operator<<(ostream &os, Deck &d) {
	for (Card c : d.cards) {
		os << cardToString(c) << endl;
	}
}

void operator<<(Deck & d2, Deck & d1)
{
	move(d1.cards.begin(), d1.cards.end(), back_inserter(d2.cards));
	d1.cards.erase(d1.cards.begin(), d1.cards.end());
	d2.shuffle();
}
