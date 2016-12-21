#pragma once



#ifndef Parsing_h
#define Parsing_h

#include "stdafx.h"
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cmath>
#include <iomanip>
#include <string>
#include <fstream>
#include <vector>
#include <iterator>     // std::back_inserter
#include "Card.h"

using namespace std;

enum Error_Values { NO_ERROR = 0, FILE_FAILED_TO_OPEN = 2, INVALID_METHOD_CALL = 3, TOO_MANY_COMMAND_ARGS = 4, NO_SHUFFLE_ARG = 5, NO_INPUT_FILE_GIVEN = 6, NO_ARGS_PASSED = 7, NOT_ENOUGH_CARDS = 8, INVALID_HAND_LOCATION = 9 };
#define SUCCESS  0
#define EXPECTED_NUM_ARGS 4
#define MIN_PLAYERS 1
string errorValueToString(Error_Values ev);

bool isPosCardDef(string cardDef);

bool isValidCard(const Card &curCard);

Card stringToCard(string cardDef);

int makeCards(vector<Card> & cards, char* fileName);

int getHandsFromDeck(vector<Card> & cards);

vector <Card> makeHandFromDeck(vector < Card> & cardSet, int &startingPoint);

Hand_Type checkDuplicates(const vector<Card> &hand);

Hand_Type checkFourKind(const vector<Card> &hand, vector<int> &pairs);
Hand_Type checkThreeKind(const vector<Card> &hand, vector<int> &pairs);

Hand_Type checkRunFiveCard(vector<Card> &hand);
Hand_Type checkRun(const vector<Card> &hand);

bool isHeart(const Card &c);
bool isClub(const Card &c);
bool isDiamond(const Card &c);
bool isSpade(const Card &c);


Hand_Type checkFlush(const vector<Card> &hand);

Hand_Type arrayToHandType(const vector<Hand_Type> &handInfo);

Hand_Type getHandType(const vector<Card> &hand);

void usageMessage(char* commandArgs[], int numArgs, int errorValue);

void usageMessage();

void putCardsInDeck(vector<Card> &h, vector<Card> &deck);

bool foundComment(string carddef);

void checkCommandArgs(char* commandArgs[], int numArgs);

bool shouldShuffle(char* args[], int numArgs);

string getFileName(char* args[], int numArgs);

#endif /* Parsing_h */
