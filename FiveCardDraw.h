#pragma once

#ifndef FiveCardDraw_h
#define FiveCardDraw_h

#include "PokerGame.h"

class FiveCardDraw : public PokerGame {
public:
	FiveCardDraw();
	virtual int before_turn(Player &p);
	virtual int turn(Player &p);
	virtual int after_turn(Player &p);
	virtual int before_round();
	virtual int round();
	virtual int after_round();

	void deckMaintenance();

	int auto_player_before_turn(Player &p);
	int auto_player_after_turn(Player &p);
};

#endif /* FiveCardDraw_h */