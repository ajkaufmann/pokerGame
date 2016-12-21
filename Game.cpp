#include "stdafx.h"
#include "FiveCardDraw.h"
#include "SevenCardStud.h"
#include "TexasHoldEm.h"
#include "Game.h"

using namespace std;

shared_ptr<Game> Game::ptr = 0;

shared_ptr<Game> Game::instance()
{
	if (ptr == 0) {
		throw INSTANCE_NOT_AVAILABLE;
	}
	else {
		return ptr;
	}
}

void Game::start_game(string gameName, char* inputs[], int numArgs)
{
	if (gameName == "FiveCardDraw") {
		ptr = make_shared<FiveCardDraw>();
		for (size_t i = 2; i < static_cast<size_t>(numArgs); ++i) {
			ptr->add_player(static_cast<string>(inputs[i]));
		}
	}
	else if (gameName == "SevenCardStud") {
		ptr = make_shared<SevenCardStud>();
		for (size_t i = 2; i < static_cast<size_t>(numArgs); ++i) {
			ptr->add_player(static_cast<string>(inputs[i]));
		}
	}
	else if (gameName == "TexasHoldEm") {
		ptr = make_shared<TexasHoldEm>();
		for (size_t i = 2; i < static_cast<size_t>(numArgs); ++i) {
			ptr->add_player(static_cast<string>(inputs[i]));
		}
	}
	else {
		throw UNKNOWN_GAME;
	}
	ptr->makeDeck();

}

void Game::stop_game()
{
	try {
		instance();
		auto pSize = ptr->num_players();
		for (auto i = 0; i < pSize; i++) {
			ptr->remove_player(ptr->players[0]->name);
		}
	}
	catch (Game_Errors) {
		throw NO_GAME_IN_PROGRESS;
	}
}

shared_ptr<Player> Game::find_player(string playerName)
{
	for (auto player : players) {
		if (player->name == playerName) {
			return player;
		}
	}
	return nullptr;
}

int Game::num_players()
{
	return players.size();
}

//the implimentation of this method allows the user to add an automatic player with the same name that will replace the other player.
void Game::add_player(const string playerName)
{
	auto loc = playerName.find("*");
	auto str = playerName;
	if (loc != string::npos) {
		str.erase(loc, 1);
	}
	auto p = find_player(str);
	if (p == nullptr) {
		players.push_back(make_shared<Player>(playerName));
		return;
	}
	else if ((loc != string::npos && !(p.get()->automatic)))
	{
		ptr->remove_player(str);
		players.push_back(make_shared<Player>(playerName));
	}
	else {
		throw ALREADY_PLAYING;
	}
}

int Game::remove_player(string pName)
{
	auto p = ptr->find_player(pName);
	if (p != 0) {
		auto toRemove = std::find(players.begin(), players.end(), p);
		ofstream ofs(toRemove->get()->name, std::ofstream::out);
		ofs << "Name: " << toRemove->get()->name << endl;
		ofs << "Wins: " << toRemove->get()->wins << endl;
		ofs << "Losses: " << toRemove->get()->loss << endl;
		ofs << "Chips: " << toRemove->get()->chips << endl;
		ofs.close();
		players.erase(toRemove);
	}
	else {
		cout << pName << " was not in the game, no file was written." << endl;
	}
	return SUCCESS;
}

void Game::makeDeck()
{
	dealer = 0;
	for (int suit = SPADE; suit > 0; suit--) {
		for (int rank = ACE; rank > 1; rank--) {
			deck.addCard(Card(static_cast<Rank>(rank), static_cast<Suit>(suit)));
		}
	}
}

void Game::changeGame(string gameName)
{
	if (gameName == "FiveCardDraw") {
		ptr = make_shared<FiveCardDraw>();
	}
	else if (gameName == "SevenCardStud") {
		ptr = make_shared<SevenCardStud>();
	}
	else if (gameName == "TexasHoldEm") {
		ptr = make_shared<TexasHoldEm>();
	}
	else if (gameName == "QUIT") {
		return;
	}
	if (ptr != nullptr) {
		ptr->makeDeck();
	}
}

void Game::check_to_change_game()
{
	bool validGame = false;
	string newGame;
	while (!validGame) {
		cout << "If you want to change the game, type the name of the new game. No input will keep the same type. 'QUIT' will quit the program." << endl;
		getline(cin, newGame);
		validGame = newGame == "" || newGame == "FiveCardDraw" || newGame == "SevenCardStud" || newGame == "TexasHoldEm" || newGame == "QUIT";
		if (!validGame) {
			cout << newGame << " is an invalid game name." << endl;
		}
	}
	if (newGame == "");
	else if (newGame == "QUIT") {
		ptr->stop_game();
		throw END_GAME;
	}
	else
	{
		ptr->stop_game();
		Game::changeGame(newGame);
		ptr= Game::instance();
		ptr->check_players_entering();
		if (ptr->num_players() < 2) {
			throw TOO_FEW_PLAYERS;
		}
	}
}

void Game::single_game()
{
	if (before_round()) {
		throw TOO_MANY_PLAYERS;
	}
	round();
	after_round();
}

void operator<<(ostream &os, Game_Errors &ge)
{
	os << "ERROR: " << endl;
	switch (ge)
	{
	case INSTANCE_NOT_AVAILABLE:
		os << "Instance is not available." << endl;
		break;
	case GAME_ALREADY_STARTED:
		os << "The game has already started." << endl;
		break;
	case UNKNOWN_GAME:
		os << "There was an unknown game input. The accepted games are SevenCardStud, FiveCardDraw, and TexasHoldEm." << endl;
		break;
	case NO_GAME_IN_PROGRESS:
		os << "There is no game in progress." << endl;
		break;
	case ALREADY_PLAYING:
		os << "That play is already playing" << endl;
		break;
	case INVALID_COMMAND_ARGUMENTS:
		os << "Those are not valid command line arguments" << endl;
		break;
	case TOO_MANY_PLAYERS:
		os << "There are too many players to play this game." << endl;
		break;
	case TOO_FEW_PLAYERS:
		os << "There are too few players to play this game, you must have at least two players in a game." << endl;
		break;
	default:
		os << "NO ERRORS" << endl;
		break;
	}
}