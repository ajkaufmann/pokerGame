#include "stdafx.h"
#include "PokerGame.h"
#include <iostream>

PokerGame::PokerGame()
{
	pot = 0;
}

PokerGame::~PokerGame()
{
}

void PokerGame::ante()
{
	chip_check();
	for (auto p : players) {
		p->betAction(1, pot);
		p->folded = false;
	}
	playersIn = players.size();
}

int PokerGame::clearBetVals()
{
	for (auto p : players) {
		p->lastBet = 0;
	}
	minBet = 0;
	return 0;
}

int PokerGame::bettingPhase() {
	clearBetVals();
	cout << "ROUND OF BETS" << endl;
	for (auto p : players) {
		playersIn -= p->betTurn(minBet, pot);
		if (playersIn < 2) {
			throw LAST_ONE_IN;
		}
	}
	unsigned int counter = 1;
	while (playersNeedToCall()) {
		cout << "CALLING PHASE: " << counter << endl;
		for (auto p : players) {
			playersIn -= p->callTurn(minBet, pot);
			if (playersIn < 2) {
				throw LAST_ONE_IN;
			}
		}
		++counter;
	}
	return 0;
}

bool PokerGame::playersNeedToCall() {
	for (auto p : players) {
		if (p->lastBet < minBet && !p->folded) {
			return true;
		}
	}
	return false;
}

void PokerGame::check_players_leaving() {
	string playerName;
	while (true) {
		cout << "Do any players want to leave? Input their name. Type 'NO' to exit." << endl;
		getline(cin, playerName);
		if ((playerName == "NO") || (playerName == "") || playerName == "No" || playerName == "no") {
			cout << endl;
			break;
		}
		auto val = ptr->remove_player(playerName); //call remove player on the game itself	
	}
}

void PokerGame::check_players_entering() {
	string playerName;
	while (true) {
		cout << "Do any players want to join the game? Input their name. Type 'NO' to exit." << endl;
		getline(cin, playerName);
		if ((playerName == "NO") || (playerName == "") || playerName == "No" || playerName == "no") {
			cout << endl;
			break;
		}
		try {
			ptr->add_player(playerName); //call add player on the game itself
		}
		catch (Game_Errors) {
			cout << playerName << " is already playing." << endl;
		}

	}
}

vector<size_t> PokerGame::check_ties(vector<shared_ptr<Player>> result) {
	vector<size_t> tieLocations;
	for (size_t i = 0; i < result.size()-1; i++) {
		if (result[i]->playerHand.ht == result[i + 1]->playerHand.ht) {
			tieLocations.push_back(i);
			tieLocations.push_back(i + 1);
			i++;
		}
	}
	vector<size_t> ties;
	for (size_t i = 0; i < tieLocations.size()- 1 && tieLocations.size() > 0; i++) {
			vector<Card> h1Ordered = arrangeHand(result[tieLocations[i]]->playerHand);
			vector<Card> h2Ordered = arrangeHand(result[tieLocations[i+1]]->playerHand);
			if (h1Ordered == h2Ordered) {
				ties.push_back(i);
				ties.push_back(i + 1);
				++i;
			}
			else {
				break;
			}
	}
	return ties;
}

void PokerGame::winManagement() {
	vector<shared_ptr<Player>> temp = players;
	std::sort(temp.begin(), temp.end(), poker_rank_player);
	temp[0]->add_win();
	temp[0]->lastResult = WON;
	auto tiedPlayersLocations = check_ties(temp);
	givePot(temp, tiedPlayersLocations);
	for (unsigned int i = 1; i < temp.size(); ++i) {
		temp[i]->add_loss();
		temp[i]->lastResult = MIDDLE;
	}
	temp[temp.size() - 1]->lastResult = LOST;
	cout << "********************************************************************" << endl;
	cout << "After round rank." << endl;
	for (size_t i = 0; i < temp.size(); ++i) {
		cout << "\t" << *temp[i];
		cout << endl;
	}
	cout << "********************************************************************" << endl;
}

void PokerGame::chip_check() {
	for (auto p : players) {
		if (!p->check_chip_reset()) {
			ptr->remove_player(p->name);
		}
	}
}

//this can throw a too few players...? might be chill to let it go all the way out
int PokerGame::player_movement()
{

	chip_check();
	check_players_leaving();
	check_players_entering();

	if (players.size() < 2) {
		throw TOO_FEW_PLAYERS;
	}

	return 0;
}

int PokerGame::givePot(vector<shared_ptr<Player>> results, vector<size_t> ties)
{
	auto split = ties.size();
	if (split == 0) {
		results[0]->chips += pot;
		pot = 0;
		return 0;
	}
	else
	{
		for (auto loc : ties) {
			results[loc]->chips += (pot / split);
		}
		pot = pot % split;
	}
	return 0;
}