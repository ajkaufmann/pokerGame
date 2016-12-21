#pragma once

#ifndef SevenCardStud_h
#define SevenCardStud_h

#include "PokerGame.h"

class SevenCardStud : public PokerGame {
public:
	unsigned int turnNum;

	SevenCardStud();
	virtual int before_turn(Player &p);
	virtual int turn(Player &p);
	int first_turn(Player &p);
	int middle_turn(Player &p);
	int last_turn(Player &p);
	virtual int after_turn(Player &p);
	virtual int before_round();
	virtual int round();
	virtual int after_round();

	void sevenCardStudHandDisplay(Player &p);
	string hiddenView(Player &p);

	void deckMaintenance();

};

#endif /* SevenCardStud_h */