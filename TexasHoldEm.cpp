#include "stdafx.h"
#include "TexasHoldEm.h"

TexasHoldEm::TexasHoldEm()
{
}

int TexasHoldEm::before_turn(Player & p)
{
	cout << "_____________________________" << endl;
	texasHoldEmHandDisplay(p);
	return SUCCESS;

}

int TexasHoldEm::turn(Player & p)
{
	cout << "__________________________________________________________" << endl;
	cout << p.name << "'s turn." << endl;
	cout << p.playerHand;
	cout << endl;

	if (turnNum == 0) {
		first_turn(p);
	}
	p.playerHand.ht = getHandType((p.playerHand + board));
	return SUCCESS;
}

int TexasHoldEm::first_turn(Player & p)
{
	p.add_card(deck.dealCard());
	p.add_card(deck.dealCard());
	return SUCCESS;
}

int TexasHoldEm::middle_turn(Player & p)
{
	return SUCCESS;
}

int TexasHoldEm::last_turn(Player & p)
{
	return SUCCESS;
}

int TexasHoldEm::after_turn(Player & p)
{
	cout << "__________________________________________________" << endl;
	return SUCCESS;
}

int TexasHoldEm::before_round()
{
	if (deck.size() < players.size() * 7) {
		return NOT_ENOUGH_CARDS;
	}

	pot = 0;
	minBet = 0;
	turnNum = 0;
	ante();
	deck.shuffle();
	return SUCCESS;
}

void TexasHoldEm::boardManagement() {
	switch (turnNum)
	{
	case 1:
	{
		for (unsigned int i = 0; i < 3; i++) {
			board << deck;
		}
		break;
	}
	case 2:
	case 3:
	{
		board << deck;
		break;
	}
	default:
		break;
	}
}

int TexasHoldEm::round()
{
	for (turnNum; turnNum < 4; turnNum++) {
		boardManagement();
		for (auto p : players) {
			before_turn(*p);
			turn(*p);
		}
		for (auto p : players) {
			cout << p->name << " " << p->playerHand.ht;
			cout << endl;
		}
		bettingPhase();
	}
	return SUCCESS;
}

int TexasHoldEm::after_round()
{
	winManagement();
	deckMaintenance();
	player_movement();
	return SUCCESS;
}

void TexasHoldEm::texasHoldEmHandDisplay(Player & p)
{
	cout << p.name << "'s Turn." << endl;
	if (turnNum < 1) return;
	for (auto cur : players) {
		if (*cur == p);
		else {
			cout << hiddenView(*cur) << endl;
		}
	}
}

string TexasHoldEm::hiddenView(Player & p)
{
	return string();
}

void TexasHoldEm::deckMaintenance()
{
	for (auto p : players) {
		discard_deck << *p;
	}
	discard_deck << board;
	deck << discard_deck;
	dealer = ((++dealer) % players.size());
}