#include "stdafx.h"
#include "SevenCardStud.h"
#include <iostream>
#include <iterator>

SevenCardStud::SevenCardStud()
{
}

int SevenCardStud::before_turn(Player & p)
{
	cout << "Players still in :" << endl;
	for (auto p : players) {
		cout << p->name;
		cout << endl;
	}
	return 0;
}

int SevenCardStud::turn(Player & p)
{
	cout << p.name << "'s turn." << endl;
	
	sevenCardStudHandDisplay(p);

	switch (turnNum)
	{
	case 0:
		first_turn(p);
		break;
	case 1:
	case 2:
	case 3:
		middle_turn(p);
		break;
	case 4:
		last_turn(p);
		break;
	default:
		break;
	}
	return 0;
}

int SevenCardStud::first_turn(Player & p)
{
	for (unsigned int i = 0; i < 2; i++) {
		Card c = deck.dealCard();
		c.facedown = true;
		p.add_card(c);
	}
	p.add_card(deck.dealCard());
	return 0;
}

int SevenCardStud::middle_turn(Player & p)
{
	p.add_card(deck.dealCard());
	return SUCCESS;
}

int SevenCardStud::last_turn(Player & p)
{
	Card c = deck.dealCard();
	c.facedown = true;
	p.add_card(c);
	return SUCCESS;
}

int SevenCardStud::after_turn(Player & p)
{
	return SUCCESS;
}

int SevenCardStud::before_round()
{
	if (deck.size() < players.size() * 7) {
		return NOT_ENOUGH_CARDS;
	}
	minBet = 0;
	turnNum = 0;
	ante();
	deck.shuffle();
	return SUCCESS;
}

int SevenCardStud::round()
{
	for (turnNum; turnNum < 5; turnNum++) {
		for (auto p : players) {
			turn(*p);
			cout << p->playerHand;
		}
		bettingPhase();
	}
	return SUCCESS;
}

int SevenCardStud::after_round()
{
	winManagement();
	deckMaintenance();
	player_movement();
	return SUCCESS;
}

void SevenCardStud::sevenCardStudHandDisplay(Player & p)
{
	if (turnNum < 1) return;
	for (auto cur : players) {
		if (*cur == p);
		else {
			cout << hiddenView(*cur) << endl;
		}
	}

}

string SevenCardStud::hiddenView(Player & p)
{
	return  p.name + ". Cards: " + p.playerHand.hiddenView();
}

void SevenCardStud::deckMaintenance()
{
	for (size_t i = 0; i < players.size(); ++i) { //clears all cards into the discard_deck
		discard_deck << *players[i];
	}
	deck << discard_deck;
	dealer = ((++dealer) % players.size());	
}