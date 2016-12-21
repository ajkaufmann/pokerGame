#pragma once

#ifndef TexasHoldEm_h
#define TexasHoldEm_h

#include "PokerGame.h"

class TexasHoldEm : public PokerGame {
public:
	Hand board;
	unsigned int turnNum;

	TexasHoldEm();
	virtual int before_turn(Player &p);
	virtual int turn(Player &p);
	int first_turn(Player &p);
	int middle_turn(Player &p);
	int last_turn(Player &p);
	virtual int after_turn(Player &p);
	virtual int before_round();
	virtual int round();
	virtual int after_round();

	void texasHoldEmHandDisplay(Player &p);
	void boardManagement();
	string hiddenView(Player &p);

	void deckMaintenance();

};

#endif /* TexasHoldEm_h */