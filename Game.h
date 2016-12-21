#pragma once

#ifndef Game_h
#define Game_h

#include "Player.h"
#include <memory>

enum Game_Errors { INSTANCE_NOT_AVAILABLE = 1, GAME_ALREADY_STARTED = 2, UNKNOWN_GAME = 3, NO_GAME_IN_PROGRESS = 4, ALREADY_PLAYING = 5, INVALID_COMMAND_ARGUMENTS = 6, TOO_MANY_PLAYERS = 7, TOO_FEW_PLAYERS = 8, END_GAME = 10 };

class Game {
protected:
	static shared_ptr<Game> ptr;
	Deck deck, discard_deck;
	vector<shared_ptr<Player>> players;
	size_t dealer;
public:
	static shared_ptr<Game> instance();
	static void start_game(char* inputs[], int numArgs);
	static void start_game(string gameName, char* inputs[], int numArgs);
	static void stop_game();
	void add_player(const string playerName);
	shared_ptr<Player> find_player(string playerName);
	int num_players();
	int remove_player(string pName);
	void makeDeck();
	static void changeGame(string gameName);
	static void check_to_change_game();
	void single_game();

	virtual int before_turn(Player &p) = 0;
	virtual int turn(Player &p) = 0;
	virtual int after_turn(Player &p) = 0;
	virtual int before_round() = 0;
	virtual int round() = 0;
	virtual int after_round() = 0;
	virtual void check_players_entering() = 0;
};

void operator<<(ostream &os, Game_Errors &ge);

#endif /* Game_h */

