#include "stdafx.h"
#include "Player.h"
#include <iostream>

Player::Player(string aName) {
	string holder;
	auto p = aName.find("*");
	if (p != string::npos) {
		aName.erase(p, 1);
		automatic = true;
	}
	else {
		automatic = false;
	}
	try {
		ifstream ifs(aName, std::ifstream::in);
		if (ifs.is_open()) {
			ifs >> holder;
			ifs >> name;
			ifs >> holder;
			ifs >> wins;
			ifs >> holder;
			ifs >> loss;
			ifs >> holder;
			ifs >> chips;
		}
		else {
			ifs.close();
			throw NOT_FULL_PLAYER_FILE;
		}
		if (holder != "Chips:") {
			ifs.close();
			throw NOT_FULL_PLAYER_FILE;
		}
		ifs.close();
	}
	catch (...) {
		name = aName;
		wins = 0;
		loss = 0;
		chips = 20;
	}
	folded = false;
}

Card Player::discard_card(size_t index)
{
	return playerHand.remove_card(index);
}

void Player::add_card(Card c) {
	playerHand << c;
}

void Player::add_win()
{
	++wins;
}

void Player::add_loss()
{
	++loss;
}

bool Player::operator==(Player & p)
{
	return p.name == name;
}

bool Player::check_chip_reset() {
	if (chips > 0) {
		return true;
	}
	cout << name << ", you have " << chips << " chips. Would you like to reset to 20? Type 'YES' to reset. Any other input will cause you to leave the game." << endl;
	string userInput;
	getline(cin, userInput);
	if (userInput == "YES") {
		chips = 20;
		return true;
	}
	else
	{
		return false;
	}
}

int Player::betAction(unsigned int amt, unsigned int &pot)
{
	try
	{
		if (amt > chips) {
			throw OVERBET;
		}
		else
		{
			chips -= amt;
			pot += amt;
			return amt;
		}
	}
	catch (Player_Errors)
	{
		string userInput;
		cout << "You don't have enough chips. Do you want to reset to 20 chips? Type 'YES' to reset chips. If you want to input a new value to bet type 'REBET.' Any other input will cause you to fold." << endl;
		getline(cin, userInput);
		cout << endl;
		if (userInput == "YES") {
			chips = 20;
			cout << "Your new chip count is " << chips << ". How much do you want to bet?" << endl;
			getline(cin, userInput);
			cout << endl;
			stringstream myStream(userInput);
			myStream >> amt;
			return betAction(amt, pot);
		}
		else if (userInput == "REBET") {
			cout << "What is your new bet? Your total chips are: " << chips << endl;
			getline(cin, userInput);
			cout << endl;
			stringstream myStream(userInput);
			myStream >> amt;
			return betAction(amt, pot);
		}
		else {
			folded = true;
			return 0;
		}
	}
}

int Player::betTurn(unsigned int &minBet, unsigned int &pot)
{
	if (folded) {
		return 0;
	}
	unsigned int betAmt = 0;
	string userInput = "";
	cout << name << " Chips: " << chips;
	cout << endl;
	cout << playerHand;
	cout << endl;
	while ((betAmt + lastBet) < minBet || minBet == 0) {
		if (minBet == 0) {
			cout << "How much do you want to bet? You can bet at most " << chips << " chip(s). To check, input 'CHECK' or type 'FOLD' to fold." << endl;
		}
		else {
			cout << "How much do you want to bet? You must bet at least " << (minBet - lastBet) << " chip(s). To fold, input 'FOLD'." << endl;
		}
		getline(cin, userInput);
		cout << endl;
		stringstream myStream(userInput);
		myStream >> betAmt;
		if (userInput == "CHECK") {
			betAmt = 0;
		}
		else if (userInput == "FOLD") {
			folded = true;
			betAmt = 0;
			lastBet += betAmt;
			return 1;
		}
		else if (betAmt > chips) {
			betAmt = betAction(betAmt, pot);
		}
		if ((betAmt + lastBet) >= minBet) {
			break;
		}
		else {
			betAction(betAmt, pot);
			lastBet += betAmt;
			betAmt = 0;
		}
	}
	if (betAction(betAmt, pot) == betAmt) {
		minBet = betAmt + lastBet;
		lastBet += betAmt;
		return 0;
	}
	else {
		return 0;
	}
}

int Player::callTurn(unsigned int &minBet, unsigned int &pot)
{
	int betAmt = 0;
	string userInput = "";
	cout << name << " Chips: " << chips;
	cout << endl;
	cout << playerHand;
	cout << endl;
	if (folded) {
		return 0;
	}
	if ((betAmt + lastBet) < minBet) {
		cout << "How much do you want to bet? You must bet at least " << (minBet - lastBet) << " chip(s). To fold, input 'FOLD'. If you bet less than the minimum amount you will fold." << endl;
		getline(cin, userInput);
		cout << endl;
		stringstream myStream(userInput);
		myStream >> betAmt;
		if (userInput == "FOLD" || (betAmt + lastBet) < minBet) {
			folded = true;
			betAmt = 0;
			lastBet += betAmt;
			return 1;
		}
	}
	if (betAction(betAmt, pot) == betAmt) {
		minBet = betAmt + lastBet;
		lastBet += betAmt;
		return 0;
	}
	else {
		folded = true;
		return 1;
	}
}

void Player::setHand(Hand &newHand) {
	playerHand = newHand;
}

void operator<<(ostream &os, Player &p) {
	os << p.name << ". Rank: " << handTypeToString(p.playerHand.ht) << " Wins: " << p.wins << ". Losses: " << p.loss << ". Chips : " << p.chips << endl;
}

void operator<<(ostream & os, shared_ptr<Player> p)
{
	os << p->name << ". Rank: " << handTypeToString(p->playerHand.ht) << " Wins: " << p->wins << ". Losses: " << p->loss << ". Chips : " << p->chips << endl;
}

void operator<<(Deck & d, Player & p)
{
	size_t handSize = p.playerHand.size();
	for (size_t i = 0; i < handSize; ++i) {
		d.addCard(p.discard_card(0));
	}
	p.playerHand.ht = NO_RANK;
	p.folded = false;
}

bool poker_rank_player(const shared_ptr<Player> p1, const shared_ptr<Player> p2)
{
	if (p1 == nullptr || p1->folded) {
		return false;
	}
	else if (p2 == nullptr || p2->folded) {
		return true;
	}
	else {
		return poker_rank(p1->playerHand, p2->playerHand);
	}
}
