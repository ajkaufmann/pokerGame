#include "stdafx.h"
#include "Parsing.h"

using namespace std;

string errorValueToString(Error_Values ev)
{
	switch (ev)
	{
	case 2:
		return "The file failed to open.";
		break;
	case 3:
		return "Invalid method call.";
		break;
	case 4:
		return "You can only pass 2 arguments into the program: The file name and a '-shuffle' argument.";
		break;
	case 5:
		return "If passing more than one argument, you must pass a '-shuffle' as a second argument.";
		break;
	case 6:
		return "There was no file given.";
		break;
	case 7:
		return "No arguments were passed into the program.";
		break;
	case 8:
		return "There were not enough cards to be dealt, check to see that your file has enough valid defintions.";
		break;
	case 0:
		return "No errors, the program ran as expected.";
	default:
		return "";
		break;
	}
}

bool isPosCardDef(string carddef) {
	return (carddef[0] != '/' && carddef.size() >= 2);
}

bool isValidCard(const Card &curCard) {
	return !(curCard.cardRank < 0 || curCard.cardSuit < 0);
}

bool foundComment(string carddef) {
	return (carddef[0] == '/' || carddef[1] == '/');
}

void putCardsInDeck(vector<Card> &h, vector<Card> &deck) {
	for (unsigned int i = 0; i < h.size(); ++i) {
		deck.push_back(h.at(i));
	}
}

Card stringToCard(string carddef) {
	Card c;
	int loc = 0;
	if (carddef[loc] == '1') {
		c.cardRank = TEN;
		loc++;
	}
	//switch statement for setting the rank
	else
	{
		switch (carddef[loc])
		{
		case 'a': c.cardRank = ACE;
			break;
		case'A': c.cardRank = ACE;
			break;
		case 'j': c.cardRank = JACK;
			break;
		case 'J': c.cardRank = JACK;
			break;
		case 'q': c.cardRank = QUEEN;
			break;
		case 'Q': c.cardRank = QUEEN;
			break;
		case 'k': c.cardRank = KING;
			break;
		case 'K': c.cardRank = KING;
			break;
		case '2': c.cardRank = TWO;
			break;
		case '3': c.cardRank = THREE;
			break;
		case '4': c.cardRank = FOUR;
			break;
		case '5': c.cardRank = FIVE;
			break;
		case '6': c.cardRank = SIX;
			break;
		case '7': c.cardRank = SEVEN;
			break;
		case '8': c.cardRank = EIGHT;
			break;
		case '9': c.cardRank = NINE;
			break;
		default: c.cardRank = INVALID_RANK;
			break;
		}
	}
	loc++;
	//switch statement for setting the suit;
	switch (carddef[loc])
	{
	case 'h': c.cardSuit = HEART;
		break;
	case'H': c.cardSuit = HEART;
		break;
	case 's': c.cardSuit = SPADE;
		break;
	case'S': c.cardSuit = SPADE;
		break;
	case 'd': c.cardSuit = DIAMOND;
		break;
	case'D': c.cardSuit = DIAMOND;
		break;
	case 'c': c.cardSuit = CLUB;
		break;
	case'C': c.cardSuit = CLUB;
		break;
	default: c.cardSuit = INVALID_SUIT;
		break;
	}
	return c;
}

int makeCards(vector<Card> & cards, char* filename) {
	ifstream ifs(filename);
	string line;
	vector<Card> hand;
	int numCards = 0;
	if (ifs.is_open()) {
		while (getline(ifs, line)) {
			istringstream iss(line);
			string singledef;
			hand.clear();
			auto goToNewLine = false;
			numCards = 0;
			while (iss >> singledef && !goToNewLine) {
				if (isPosCardDef(singledef)) {
					if (!foundComment(singledef)) {
						Card newcard = stringToCard(singledef);
						if (isValidCard(newcard)) {
							hand.push_back(newcard);
							numCards++;
						}
					}
					else {
						break;
					}
				}
				if (singledef.size() >= 4 && singledef[3] == '/') {
					goToNewLine = true;
				}
			}
			if (numCards == 5) {
				putCardsInDeck(hand, cards);
			}
			else if (line != "") {
				cout << "The line: " << line << " was not read into the file because there is/are " << numCards << " valid cards." << endl;
			}
		}
		ifs.close();
	}
	else {
		return FILE_FAILED_TO_OPEN; //filestream didn't open
	}
	return NO_ERROR;

}

int getHandsFromDeck(vector<Card> & cards) {
	int locOfHand = 0;
	vector<Card> hand;
	while ((size_t)locOfHand < cards.size()) {
		hand = makeHandFromDeck(cards, locOfHand);
		printCards(hand);
		std::sort(cards.begin(), cards.end());
		Hand_Type ht = getHandType(hand);
		hand.clear();
		cout << endl;
	}
	return NO_ERROR;

}

vector <Card> makeHandFromDeck(vector <Card> & cardSet, int &startingPoint) {
	vector<Card> aHand;
	for (int i = 0; i < 5; ++i) {
		aHand.push_back(cardSet[i + startingPoint]);
	}
	startingPoint += 5;
	std::sort(aHand.begin(), aHand.end());
	return aHand;
}

enum Hand_Type getHandType(const vector<Card> &hand) {
	vector<Hand_Type> resultArray;
	resultArray.push_back(checkDuplicates(hand));
	resultArray.push_back(checkRun(hand));
	resultArray.push_back(checkFlush(hand));
	Hand_Type result = arrayToHandType(resultArray);
	//cout << handTypeToString(result) << endl;
	return result;
}

Hand_Type checkDuplicates(const vector<Card> &hand) {
	vector<int> pairs;
	for (size_t i = 0; i < hand.size(); i++) {
		pairs.push_back(0);
	}

	for (size_t i = 0; i < hand.size(); ++i) {
		for (size_t j = i + 1; j < hand.size(); j++) {
			if (hand[i].cardRank == hand[j].cardRank) { //check if the cards are the same
				pairs[i] = 1;
				pairs[j] = 1;
			}
		}
	}
	
	int sum = 0;
	for (int i : pairs) {
		sum += i;
	}

	Hand_Type highest_duplicate_result;
	switch (sum)
	{
	case 2:
		highest_duplicate_result = PAIR_HAND;
		break;
	case 3:
		highest_duplicate_result = THREE_OF_KIND;
		break;
	case 4:
		highest_duplicate_result = checkFourKind(hand, pairs);
		break;
	case 5:
		highest_duplicate_result = FULL_HOUSE;
	case 6:
	{
		Hand_Type threeCheck = checkThreeKind(hand, pairs);
		Hand_Type fourCheck = checkFourKind(hand, pairs);
		highest_duplicate_result = max(threeCheck, fourCheck);
		break;
	}
	case 7: 
	{
		Hand_Type threeCheck = checkThreeKind(hand, pairs);
		Hand_Type fourCheck = checkFourKind(hand, pairs);
		if (fourCheck == TWO_PAIR && threeCheck == THREE_OF_KIND) {
			highest_duplicate_result = FULL_HOUSE;
		}
		else {
			highest_duplicate_result = fourCheck;
		}
	}
	default:
		highest_duplicate_result = NO_RANK;
		break;
	}

	return highest_duplicate_result;
}

Hand_Type checkFourKind(const vector<Card>& hand, vector<int>& pairs)
{
	for (size_t i = 0; i <= hand.size() - 4; i++) {
		if (hand[i].cardRank == hand[i + 3].cardRank) {
			return FOUR_OF_KIND;
		}
	}
	return TWO_PAIR;
}

Hand_Type checkThreeKind(const vector<Card>& hand, vector<int>& pairs)
{
	for (size_t i = 0; i <= hand.size() - 4; i++) {
		if (hand[i].cardRank == hand[i + 2].cardRank) {
			return THREE_OF_KIND;
		}
	}
	return TWO_PAIR;
}

Hand_Type checkRunFiveCard(vector<Card> &hand) {

	if (hand.size() < 5) return NO_RANK;
	//special case that there is an ace
	if (hand[hand.size() - 1].cardRank == ACE) { //if there is an ace
		if (hand[0].cardRank == TWO || hand[0].cardRank == TEN) { //make sure that the first card is either a 2 or 10 for possible runs
			for (unsigned int i = 1; i < hand.size() - 1; ++i) { //don't check for the last value (it's the ace!)
				if (hand[i - 1].cardRank == hand[i].cardRank - 1); // if they are equal continue check
				else { //if they are not, it's not a run so set to 0 and exit. 
					return NO_RANK;
				}
			}
		}
		else {
			return NO_RANK;
		}
	}
	else {
		for (unsigned int i = 1; i < hand.size(); ++i) {
			if (hand[i - 1].cardRank == hand[i].cardRank - 1);
			else {
				return NO_RANK;
			}
		}
	}

	return STRAIGHT;

}

//this will also check if it's going to be a straight flush
Hand_Type checkRun(const vector<Card> &hand) {
	if (hand.size() < 5) return NO_RANK;
	std::vector<Card> subvector;
	for (size_t i = 0; i <= hand.size() - 5; i++) { 
		copy(hand.begin() + i, hand.begin() + (i+5), std::back_inserter(subvector));
		if (checkRunFiveCard(subvector) == STRAIGHT) {
			if (checkFlush(subvector) == FLUSH_HAND) {
				return STRAIGHT_FLUSH;
			}
			return STRAIGHT;
		}
		subvector.clear();
	}
	return NO_RANK;
}

bool isHeart(const Card & c)
{
	return c.cardSuit == HEART;
}

bool isClub(const Card & c)
{
	return c.cardSuit == CLUB;
}

bool isDiamond(const Card & c)
{
	return c.cardSuit == DIAMOND;
}

bool isSpade(const Card & c)
{
	return c.cardSuit == SPADE;
}

Hand_Type checkFlush(const vector<Card> &hand) {

	vector<int> nums;

	nums.push_back(count_if(hand.begin(), hand.end(), isHeart));
	nums.push_back(count_if(hand.begin(), hand.end(), isDiamond));
	nums.push_back(count_if(hand.begin(), hand.end(), isClub));
	nums.push_back(count_if(hand.begin(), hand.end(), isSpade));

	int n = *std::max_element(nums.begin(), nums.end());

	if (n >= 5) {
		return FLUSH_HAND;
	}
	return NO_RANK;
}

Hand_Type arrayToHandType(const vector<Hand_Type> &handInfo) {
	if (handInfo[1] == STRAIGHT && handInfo[0] == FLUSH_HAND) return STRAIGHT_FLUSH;
	else {
		return *max_element(handInfo.begin(), handInfo.end());
	}
}

void usageMessage(char* commandArgs[], int numArgs, int errorValue) {
	if (errorValue != 0) {
		if (numArgs > 1) {
			cout << "The arguments recieved were: ";
			for (int i = 1; i < numArgs; ++i) {
				cout << commandArgs[i] << " ";
			}
			cout << endl;
			if (errorValue > 0) {
				cout << "The error with your arguments passed was: " << errorValueToString((Error_Values)errorValue) << endl;
			}
		}
	}
}

void usageMessage() {
	cout << "The program should be run with the name (FiveCardDraw, SevenCardStud, TexasHoldEm) of the game followed by the names of two or more players." << endl;
}

bool Card::operator==(const Card &ct) const {
	return (cardRank == ct.cardRank);
}

void checkCommandArgs(char* commandArgs[], int numArgs) {
	switch (numArgs)
	{
	case 1:
		throw NO_ARGS_PASSED;
		break;
	case 2:
		if (static_cast<string> (commandArgs[1]) == "-shuffle") {
			throw NO_INPUT_FILE_GIVEN;
		}
		break;
	case 3:
	{
		if (static_cast<string> (commandArgs[1]) == "-shuffle" || static_cast<string> (commandArgs[2]) == "-shuffle") {
			return;
		}
		else {
			throw NO_SHUFFLE_ARG;
		}
		break;
	}
	default:
		throw TOO_MANY_COMMAND_ARGS;
		break;
	}
}

bool shouldShuffle(char* commandArgs[], int numArgs) {
	for (int i = 1; i < numArgs; ++i) {
		if (static_cast<string> (commandArgs[i]) == "-shuffle") {
			return true;
		}
	}
	return false;
}

string getFileName(char* commandArgs[], int numArgs) {
	for (int i = 1; i < numArgs; ++i) {
		string arg = commandArgs[i];
		auto pos = arg.find(".");
		if (pos > arg.length());
		else {
			string fileEnding = arg.substr(pos);
			if (fileEnding == ".txt") return arg;
		}
	}
	throw NO_INPUT_FILE_GIVEN;
	return "";
}