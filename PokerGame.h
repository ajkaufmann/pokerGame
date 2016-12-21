#pragma once

#ifndef PokerGame_h
#define PokerGame_h

#include "Game.h"

enum Poker_Errors {LAST_ONE_IN = 1};

class PokerGame : public Game
{
public:
	unsigned int pot, minBet, playersIn;

	PokerGame();
	~PokerGame();

	void ante();
	int clearBetVals();
	int bettingPhase();
	vector<size_t> check_ties(vector<shared_ptr<Player>> result);
	int givePot(vector<shared_ptr<Player>> results, vector<size_t> ties);
	bool playersNeedToCall();

	void check_players_leaving();
	virtual void check_players_entering();
	void winManagement();
	void chip_check();
	int player_movement();
};

#endif /* PokerGame_h */
