// Lab04.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SevenCardStud.h"

using namespace std;

int main(int argc, char * argv[])
{
	if (argc < EXPECTED_NUM_ARGS) {
		usageMessage();
		return INVALID_COMMAND_ARGUMENTS;
	}
	try {
		string gameType = argv[1];
		Game::start_game(gameType, argv, argc);
		shared_ptr<Game> curGame = Game::instance();
		int eval = 0;
		while (curGame->num_players() > MIN_PLAYERS)
		{
			try
			{
				curGame->single_game();
			}
			catch (Poker_Errors) // this means that there is only one person left and the automatically win so skip all other turns in the game
			{
				curGame->after_round();
			}
			Game::check_to_change_game();
			curGame = Game::instance();
		}
		curGame->stop_game();
		return NO_ERROR;
	}
	catch (Error_Values ev) {
		cout << errorValueToString(ev) << endl;
		return ev;
	}
	catch (Game_Errors ge) {
		if (ge == END_GAME) {
			return NO_ERROR;
		}
		cout << ge;
		return ge;
	}
}

