#pragma once

#ifndef Player_h
#define Player_h

#include "Hand.h"

enum Player_Errors { NOT_FULL_PLAYER_FILE = 0, OVERBET = 1 };
enum Player_Location { WON = 0, LOST = 1, MIDDLE = 2 };

struct Player {
public:
	string name;
	Hand playerHand;
	unsigned int wins, loss, chips, lastBet;
	bool automatic, folded;
	Player_Location lastResult;

	Player(string aName);

	Card discard_card(size_t index);
	void add_card(Card c);
	void add_win();
	void add_loss();
	bool Player::operator==(Player &p);

	bool check_chip_reset();

	int betAction(unsigned int amt, unsigned int &pot);
	int betTurn(unsigned int &minBet, unsigned int &pot);
	int callTurn(unsigned int &minBet, unsigned int &pot);
	void setHand(Hand &newHand);
};

bool poker_rank_player(const shared_ptr<Player> p1, const shared_ptr<Player> p2);
void operator<<(ostream &os, Player &p);
void operator<<(ostream &os, shared_ptr<Player> p);
void operator<<(Deck &d, Player &p);



#endif /* Player_h */