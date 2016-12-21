#include "stdafx.h"
#include "FiveCardDraw.h"
#include <iostream>
#include <iterator>

using namespace std;

FiveCardDraw::FiveCardDraw()
{
}

int FiveCardDraw::auto_player_before_turn(Player & p) {
	unsigned int startHandSize = p.playerHand.size();
	cout << "Auto Player" << p.name << " BEFORE discarding cards:" << endl;
	cout << p.playerHand;
	cout << endl;
	switch (p.playerHand.ht)
	{
	case STRAIGHT_FLUSH:
	case FULL_HOUSE:
	case STRAIGHT:
	case FLUSH_HAND:
	{
		return SUCCESS;
		break;
	}
	case TWO_PAIR:
	case FOUR_OF_KIND:
	{
		auto discardIndex = findCLocation(p.playerHand);
		discard_deck.addCard(p.discard_card(discardIndex));
		break;
	}
	case THREE_OF_KIND:
	{
		auto discardIndex = findUnmatchedThreeOfKind(p.playerHand);
		discard_deck.addCard(p.discard_card(discardIndex));
		--discardIndex;
		discard_deck.addCard(p.discard_card(discardIndex));
		break;
	}
	case PAIR_HAND:
	{
		int pairLocation = getPairLocation(p.playerHand);
		int numRemoved = 0;
		for (int i = 0; i < pairLocation; i++) {
			discard_deck.addCard(p.discard_card(0));
			++numRemoved;
		}
		int adjuster = 0;
		for (unsigned int i = 2; adjuster < 3 - numRemoved; i++) {
			discard_deck.addCard(p.discard_card(i - adjuster));
			++adjuster;
		}
		break;
	}
	case NO_RANK:
	{

		if (p.playerHand[p.playerHand.size() - 1].cardRank == ACE) {
			for (unsigned int i = 0; i < startHandSize - 1; ++i) {
				discard_deck.addCard(p.discard_card(0));
			}
		}
		else
		{
			for (unsigned int i = 0; i < startHandSize - 2; ++i) {
				discard_deck.addCard(p.discard_card(0));
			}
		}
		break;
	}
	default:
		break;
	}
	cout << "Auto Player " << p.name << " AFTER discarding cards:" << endl;
	cout << p.playerHand;
	cout << endl;
	return SUCCESS;
}

int FiveCardDraw::before_turn(Player & p)
{
	if (p.automatic) {
		return auto_player_before_turn(p);
	}
	else if (p.folded) {
		return SUCCESS;
	}
	string userInput = "";
	size_t index = -1;
	cout << p;
	cout << endl;
	cout << p.playerHand;
	cout << endl;
	while (true) {
		cout << "What cards would you like to discard? Input the index of the cards you want. No input indicates no discarded cards If inputting multiple indexes, they must be in increasing order." << endl;
		getline(cin, userInput);
		if ((userInput == "NO") || (userInput == "") || userInput == "No" || userInput == "no") {
			cout << "------------------------------------------" << endl;
			break;
		}
		stringstream myStream(userInput);
		auto adjuster = 0;
		while (myStream >> index) {
			try {
				index -= adjuster;
				discard_deck.addCard(p.discard_card(index));
				index = -1;
				cout << p.playerHand;
				cout << endl;
				adjuster++;
			}
			catch (Error_Values) {
				cout << index << " is an invalid hand location. Try again." << endl;
			}
		}
	}
	return SUCCESS;
}

int FiveCardDraw::turn(Player & p)
{
	if (p.folded) {
		p.playerHand.ht = FOLDED;
		return SUCCESS;
	}
	try {
		while (p.playerHand.size() < 5) {
			p.add_card(deck.dealCard());
		}
		p.playerHand.sortHand();
	}
	catch (Error_Values) {
		//if here then there isn't enough cards in deck so need to move from discarded deck to deck
		deck << discard_deck;
		try {
			while (p.playerHand.size() < 5) {
				p.add_card(deck.dealCard());
			}

		}
		catch (Error_Values) {
			//if here there aren't enough cards in the discarded deck either so have to return a non-zero value
			return NOT_ENOUGH_CARDS;
		}

	}
	return SUCCESS;
}

int FiveCardDraw::auto_player_after_turn(Player &p) {
	cout << p;
	cout << endl;
	switch (p.lastResult)
	{
	case WON:
	{
		if (rand() % 100 > 89) {
			cout << p.name << " has left the game." << endl;
			ptr->remove_player(p.name);
		}
		break;
	}
	case LOST:
	{
		if (rand() % 100 > 9) {
			cout << p.name << " has left the game." << endl;
			ptr->remove_player(p.name);
		}
		break;
	}
	case MIDDLE:
	{
		if (rand() % 100 > 49) {
			cout << p.name << " has left the game." << endl;
			ptr->remove_player(p.name);
		}
		break;
	}
	default:
		break;
	}
	return SUCCESS;
}

int FiveCardDraw::after_turn(Player & p)
{
	if (p.automatic) {
		return auto_player_after_turn(p);
	}
	cout << p;
	cout << endl;
	return SUCCESS;
}

int FiveCardDraw::before_round()
{
	deck.shuffle();
	pot = 0;
	minBet = 0;
	ante();
	if (deck.size() < players.size() * 5) {
		return NOT_ENOUGH_CARDS;
	}
	for (int i = (dealer + 1) % players.size(); players[dealer]->playerHand.size() < 5 && deck.size() > 0; i = ((++i) % players.size())) {
		players[i]->add_card(deck.dealCard());
	}
	size_t counter = 0;
	bettingPhase();
	for (int i = ((dealer + 1) % players.size()); counter < players.size(); i = ((++i) % players.size())) {
		before_turn(*players[i]);
		counter++;
	}
	return SUCCESS;
}

int FiveCardDraw::round()
{
	int eval;
	unsigned int counter = 0;
	for (int i = (dealer + 1) % players.size(); counter < players.size(); i = ((++i) % players.size())) {
		eval = turn(*players[i]);
		if (eval) {
			return eval;
		}
		++counter;
	}
	bettingPhase();
	counter = 0;
	for (int i = (dealer + 1) % players.size(); counter < players.size(); i = ((++i) % players.size())) {
		after_turn(*players[i]);
		++counter;
	}
	return SUCCESS;
}

int FiveCardDraw::after_round()
{
	winManagement();
	deckMaintenance();
	player_movement();
	return SUCCESS;
}

void FiveCardDraw::deckMaintenance() {
	for (size_t i = 0; i < players.size(); ++i) { //clears all cards into the discard_deck
		discard_deck << *players[i];
	}
	deck << discard_deck;
	dealer = ((++dealer) % players.size());
}