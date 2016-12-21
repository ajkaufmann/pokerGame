#include <iterator>
#include "stdafx.h"
#include "Hand.h"
#include "Player.h"

Hand::Hand() {
	ht = NO_RANK;
}

Hand::Hand(const Hand &h) {
	for (unsigned int i = 0; i < h.cards.size(); i++) {
		cards.push_back(h.cards[i]);
	}
	ht = h.ht;
}

Hand& Hand::operator=(const Hand &h) {
	if (!(this == &h)) {
		cards.clear();
		for (unsigned int i = 0; i < h.cards.size(); i++) {
			cards.push_back(h.cards[i]);
		}
		ht = h.ht;
	}
	return *this;
}

vector<Card> Hand::operator+(const Hand & h)
{
	vector<Card> merged;
	copy(h.cards.begin(), h.cards.end(), back_inserter(merged));
	copy(cards.begin(), cards.end(), back_inserter(merged));
	sort(merged.begin(), merged.end());
	return merged;
}

//destructor

bool Hand::operator==(Hand &h) {
	
	for (unsigned int i = 0; i < h.cards.size(); i++) {
		if (!(cards[i] == h.cards[i])) {
			return false;
		}
	}
	return true;
}

bool Hand::operator<(const Hand &h) {
	return (ht < h.ht);
}

Card Hand::operator[](size_t index) {
	try
	{
		Card result = cards[index];
		return result;
	}
	catch (const std::exception&)
	{
		throw INVALID_HAND_LOCATION;
	}

}

Card Hand::remove_card(size_t index) {
	if (index >= cards.size() || index < 0) {
		throw INVALID_HAND_LOCATION;
	}
	else {
		auto it = std::find(cards.begin(), cards.end(), cards[index]);
		if (it != cards.end()) {
			Card c(it->cardRank, it->cardSuit);
			cards.erase(it);
			return c;
		}
		return Card(); //never reach here so doesn't matter that it's throwing an empty card. Only here to make compiler happy and not throw errors
	}
}

void Hand::sortHand()
{
	std::sort(cards.begin(), cards.end());
	ht = getHandType(cards);
}

unsigned int Hand::size() {
	return cards.size();
}

string Hand::asString() const {
	string output = "Hand: ";
	for (unsigned int i = 0; i < cards.size(); i++) {
		output += cardToString(cards[i]) + " ";
	}
	output += "| Rank: " + handTypeToString(ht);
	return output;
}

void operator<<(ostream &os, Hand &h) {
	os << "Hand Type: " << handTypeToString(h.ht) << endl;
	if (h.ht != FOLDED) {
		for (Card c : h.cards) {
			os << "\t" << cardToString(c) << endl;
		}
	}
}

//take the top card (last card) from of the deck, then sort the hand and give it a Hand_Type
void operator<<(Hand &h, Deck &d) {
	h.cards.push_back(d.getCards().back());
	d.getCards().pop_back();
	std::sort(h.cards.begin(), h.cards.end());
	h.ht = getHandType(h.cards);
}

void operator<<(Hand &h, Card c)
{
	h.cards.push_back(c);
	std::sort(h.cards.begin(), h.cards.end());
	h.ht = getHandType(h.cards);
}

void operator<<(Deck & d, Hand & h)
{
	size_t handSize = h.size();
	for (size_t i = 0; i < handSize; ++i) {
		d.addCard(h.remove_card(0));
	}
	h.ht = NO_RANK;
}

bool poker_rank(const Hand & h1, const Hand & h2)
{
	if (h1.ht == h2.ht) {
		switch (h1.ht)
		{
		case STRAIGHT_FLUSH:
		{
			//still wouldn't really work? But like?
			return h2.cards[h2.cards.size() - 1] < h1.cards[h1.cards.size() - 1];
			break;
		}
		case FOUR_OF_KIND:
		{
			vector<Card> h1Ordered = arrangeFourKind(h1);
			vector<Card> h2Ordered = arrangeFourKind(h2);

			for (size_t i = 0; i < h1Ordered.size() && i < 5; i++) {
				if (h1Ordered[i] == h2Ordered[i]);
				else {
					return  h2Ordered[i] < h1Ordered[i];
				}
			}

			break;
		}
		case FULL_HOUSE:
		{

			vector<Card> h1Ordered = arrangeFullHouse(h1);
			vector<Card> h2Ordered = arrangeFullHouse(h2);

			for (size_t i = 0; i < h1Ordered.size() && i < 5; i++) {
				if (h1Ordered[i] == h2Ordered[i]);
				else {
					return  h2Ordered[i] < h1Ordered[i];
				}
			}

			//bool h1C1 = h1.cards[0].cardRank == h1.cards[2].cardRank; //check if group of 3 is in first 3 locations
			//bool h2C1 = h2.cards[0].cardRank == h2.cards[2].cardRank; // check if group of 3 is in first 3 locations
			//if (h1C1 == h2C1) { //if group of 3 is in first 3 for both hands
			//	if (h1.cards[0].cardRank == h2.cards[0].cardRank) {  // check if group of 3 is same card rank
			//		return h2.cards[4] < h1.cards[4]; // return if h1 two group is bigger than h2's group two
			//	}
			//}
			//else if (h1C1 && !h2C1) { //group of 3 in first 3 for h1 but not h2
			//	if (h1.cards[0].cardRank == h2.cards[4].cardRank) {  // check if group of 3 is same card rank
			//		return h2.cards[0] < h1.cards[4]; // return if h1 two group is bigger than h2's group two
			//	}
			//}
			//else if (!h1C1 && h2C1) { //group of 3 in first 3 for h2 but not h1
			//	if (h1.cards[4].cardRank == h2.cards[0].cardRank) {  // check if group of 3 is same card rank
			//		return h2.cards[4] < h1.cards[0]; // return if h1 two group is bigger than h2's group two
			//	}
			//}
			//else if (!h1C1 && !h2C1) { //group of 3 in last 3 for h2 and h1
			//	if (h1.cards[4].cardRank == h2.cards[4].cardRank) {  // check if group of 3 is same card rank
			//		return h2.cards[0] < h1.cards[0]; // return if h1 two group is bigger than h2's group two
			//	}
			//}
			break;
		}
		case FLUSH_HAND:
		{
			vector<Card> h1Ordered = arrangeFlush(h1);
			vector<Card> h2Ordered = arrangeFlush(h2);

			for (size_t i = 0; i < h1Ordered.size() && i < 5; i++) {
				if (h1Ordered[i] == h2Ordered[i]);
				else {
					return  h2Ordered[i] < h1Ordered[i];
				}
			}
			break;
		}
		case STRAIGHT:
		{
			vector<Card> h1Ordered = arrangeStraight(h1);
			vector<Card> h2Ordered = arrangeStraight(h2);

			for (size_t i = 0; i < h1Ordered.size() && i < 5; i++) {
				if (h1Ordered[i] == h2Ordered[i]);
				else {
					return  h2Ordered[i] < h1Ordered[i];
				}
			}
			break;
		}
		case THREE_OF_KIND:
		{
			vector<Card> h1Ordered = arrangeThreeKind(h1);
			vector<Card> h2Ordered = arrangeThreeKind(h2);

			for (size_t i = 0; i < h1Ordered.size() && i < 5; i++) {
				if (h1Ordered[i] == h2Ordered[i]);
				else {
					return  h2Ordered[i] < h1Ordered[i];
				}
			}
			break;
		}
		case TWO_PAIR:
		{
			vector<Card> h1Ordered = arrange2PairHand(h1);
			vector<Card> h2Ordered = arrange2PairHand(h2);

			for (size_t i = 0; i < 5; i++) {
				if (h1Ordered[i] == h2Ordered[i]);
				else {
					return h2Ordered[i] < h1Ordered[i];
				}
			}
			break;
		}
		case PAIR_HAND:
		{
			auto h1Cards = arrangePairHand(h1);
			auto h2Cards = arrangePairHand(h2);
			if (h1Cards[0].cardRank == h2Cards[0].cardRank) {
				for (int i = 4; i >= 0; i--) { // cuz only want to check the first 5 cards
					if (h1Cards[i].cardRank == h2Cards[i].cardRank);
					else return h2Cards[i] < h1Cards[i];
				}
			}
			else return h2Cards[0] < h1Cards[0];
			break;
		}
		case NO_RANK:
		{
			for (int i = 4; i >= 0; i--) {
				if (h1.cards[i].cardRank == h2.cards[i].cardRank);
				else return h2.cards[i] < h1.cards[i];
			}
		}
		default:
		{
			return false;
			break;
		}
		}
	}
	return h2.ht < h1.ht;
}

int getPairLocation(const Hand & h)
{
	if (h.ht != PAIR_HAND) throw Error_Values::INVALID_METHOD_CALL;
	for (unsigned int i = 0; i < h.cards.size() - 1; i++) {
		if (h.cards[i].cardRank == h.cards[i + 1].cardRank) {
			return i;
		}
	}
	return -1;
}

vector<Card> arrangePairHand(const Hand &h) {
	int pairLoc = getPairLocation(h);
	if (pairLoc <= 0) return h.cards;
	vector<Card> vt;
	for (int i = pairLoc; i <= pairLoc + 1; i++) {
		vt.push_back(h.cards[i]);
	}
	for (unsigned int i = pairLoc + 2; i < h.cards.size(); i++) {
		vt.push_back(h.cards[i]);
	}
	for (int i = 0; i < pairLoc; i++) {
		vt.push_back(h.cards[i]);
	}
	return vt;
}

//FIXME FOR SIZES THAT ARE NOT 5? OR MAKE ONLY OKAY FOR SIZES THAT ARE FIVE. THIS ALL STEMS AROUND THE ISSUES OF WIN MANAGEMENT
//returns the index of a the non-paired card in the two pair hand
int findCLocation(const Hand &h) {
	if (h.cards.size() != 5) return -1;
	int unpairedIndex = 2;
	if (h.cards[4].cardRank != h.cards[3].cardRank && h.cards[0].cardRank == h.cards[1].cardRank) {
		unpairedIndex = 4;
	}
	else if (h.cards[0].cardRank != h.cards[1].cardRank && h.cards[3].cardRank == h.cards[4].cardRank) {
		unpairedIndex = 0;
	}
	return unpairedIndex;
}

//arrange hands to be easy to check 2 pair cases
vector<Card> arrange2PairHand(const Hand &h) {
	if (h.ht != TWO_PAIR) throw Error_Values::INVALID_METHOD_CALL;
	vector<size_t> pairLocs, unpairedLocs;
	vector<Card> vt;
	Hand copyHand = h;
	int i;
	for (i = h.cards.size() - 1; i >= 1; i--) {
		if (copyHand[i] == copyHand[i - 1]) {
			pairLocs.push_back(i);
			pairLocs.push_back(i - 1);
			i--;
		}
		else {
			unpairedLocs.push_back(i);
		}
	}
	for (int k = i; k >= 0; k--) {
		unpairedLocs.push_back(k);
	}

	for (auto loc : pairLocs) {
		vt.push_back(copyHand[loc]);
	}
	for (auto loc : unpairedLocs) {
		vt.push_back(copyHand[loc]);
	}
	return vt;

	/*int cLocation = findCLocation(h);
	vector<Card> vt;
	for (int i = 0; i < cLocation; i++) {
		vt.push_back(h.cards[i]);
	}
	for (unsigned int i = cLocation + 1; i < h.cards.size(); i++) {
		vt.push_back(h.cards[i]);
	}
	vt.push_back(h.cards[cLocation]);
	return vt;*/
}

int findUnmatchedThreeOfKind(const Hand &h) {
	if (h.cards[0].cardRank == h.cards[2].cardRank) {
		return THREE;
	}
	else {
		return 0;
	}
}

vector<Card> arrangeThreeKind(const Hand & h)
{
	vector<size_t> matchedLocs, unpairedLocs;
	vector<Card> vt;
	Hand copyHand = h;
	size_t i;
	for (i = h.cards.size() - 1; i >= 2; i--) {
		if (h.cards[i] == h.cards[i - 1] && h.cards[i - 1] == h.cards[i - 2]) {
			matchedLocs.push_back(i);
			matchedLocs.push_back(i - 1);
			matchedLocs.push_back(i - 2);
			i -= 2;
		}
		else
		{
			unpairedLocs.push_back(i);
		}
	}

	for (int j = i; j >= 0; j--) {
		unpairedLocs.push_back(j);

	}
	for (auto loc : matchedLocs) {
		vt.push_back(copyHand[loc]);
	}
	for (auto loc : unpairedLocs) {
		vt.push_back(copyHand[loc]);
	}
	return vt;
}

vector<Card> arrangeFullHouse(const Hand & h)
{
	vector<size_t> matchedLocs, unpairedLocs;
	Rank tripleRank = INVALID_RANK;
	vector<Card> vt;
	Hand copyHand = h;
	size_t i;
	for (i = h.cards.size() - 1; i >= 2; i--) {
		if (h.cards[i] == h.cards[i - 1] && h.cards[i - 1] == h.cards[i - 2]) {
			matchedLocs.push_back(i);
			matchedLocs.push_back(i - 1);
			matchedLocs.push_back(i - 2);
			tripleRank = h.cards[i].cardRank;
			i -= 2;
		}
		else {
			unpairedLocs.push_back(i);
		}
	}
	for (int j = i; j >= 0; j--) {
		unpairedLocs.push_back(j);
	}

	for (size_t i = h.cards.size() - 1; i >= 1; i--) {
		if (h.cards[i] == h.cards[i - 1] && h.cards[i].cardRank != tripleRank) {
			matchedLocs.push_back(i);
			matchedLocs.push_back(i - 1);
			auto it = std::find(unpairedLocs.begin(), unpairedLocs.end(), i);
			unpairedLocs.erase(it);
			i--;
			it = std::find(unpairedLocs.begin(), unpairedLocs.end(), i);
			unpairedLocs.erase(it);
		}
		else {
			unpairedLocs.push_back(i);
		}
	}

	for (auto loc : matchedLocs) {
		vt.push_back(copyHand[loc]);
	}
	for (auto loc : unpairedLocs) {
		vt.push_back(copyHand[loc]);
	}
	return vt;
}

vector<Card> arrangeFourKind(const Hand & h)
{
	vector<size_t> matchedLocs, unpairedLocs;
	vector<Card> vt;
	Hand copyHand = h;
	bool add = true;
	size_t i;
	for (i = h.cards.size() - 1; i >= 3; i--) {
		if (h.cards[i] == h.cards[i - 1] && h.cards[i - 1] == h.cards[i - 2] && h.cards[i - 2] == h.cards[i - 3]) {
			matchedLocs.push_back(i);
			matchedLocs.push_back(i - 1);
			matchedLocs.push_back(i - 2);
			matchedLocs.push_back(i - 3);
			i -= 3;
		}
		else
		{
			unpairedLocs.push_back(i);
		}
	}

	for (int j = i; j >= 0; j--) {
		unpairedLocs.push_back(j);
	}

	for (auto loc : matchedLocs) {
		vt.push_back(copyHand[loc]);
	}
	for (auto loc : unpairedLocs) {
		vt.push_back(copyHand[loc]);
	}
	return vt;
}

vector<Card> arrangeStraight(const Hand &h) {
	size_t endLoc;
	vector<Card> vt;
	std::vector<Card> subvector;
	for (size_t i = h.cards.size() - 1; i >= 5; i--) {
		copy(h.cards.begin() + (i - 5), h.cards.begin() + (i), std::back_inserter(subvector));
		if (checkRunFiveCard(subvector) == STRAIGHT) {
			endLoc = i;
		}
		subvector.clear();
	}
	for (auto i = endLoc; i > endLoc - 5; i--) {
		vt.push_back(h.cards[i]);
	}
	if (vt[0].cardRank == ACE && vt[1].cardRank == FIVE) {
		Card holder = vt[0];
		vt.erase(vt.begin());
		vt.push_back(holder);
	}

	return vt;
}

vector<Card> arrangeFlush(const Hand &h) {
	vector<Card> vt, subvector;
	remove_const<vector<Card>>::type h1 = h.cards;
	std::sort(h1.begin(), h1.end(), same_suit); // this is breaking for some reason not really sure?
	size_t endLoc = h1.size();
	for (size_t i = h.cards.size(); i >= 5; i--) {
		copy(h1.begin() + (i - 5), h1.begin() + i, std::back_inserter(subvector));
		if (checkFlush(subvector) == FLUSH_HAND) {
			endLoc = i-1;
			break;
		}
		subvector.clear();
	}
	for (auto i = endLoc; i > endLoc - 5; i--) {
		vt.push_back(h1[i]);
	}

	return vt;
}

string Hand::hiddenView()
{
	string output;
	for (Card c : cards) {
		if (c.facedown) {
			output += "* ";
		}
		else
		{
			output += cardToString(c) + " ";
		}
	}
	return output;
}

vector<Card> arrangeHand(Hand &h) {
	switch (h.ht)
	{
	case STRAIGHT_FLUSH:
	{
		return arrangeStraight(h);
		break;
	}
	case FOUR_OF_KIND:
	{
		return arrangeFourKind(h);
		break;
	}
	case FULL_HOUSE:
	{

		return arrangeFourKind(h);
	}
	case FLUSH_HAND:
	{
		return arrangeFlush(h);
	}
	case STRAIGHT:
	{
		return arrangeStraight(h);
	}
	case THREE_OF_KIND:
	{
		return arrangeThreeKind(h);
	}
	case TWO_PAIR:
	{
		return arrange2PairHand(h);
	}
	case PAIR_HAND:
	{
		return arrangePairHand(h);
	}
	case NO_RANK:
	{
		Hand copyHand = h;
		std::reverse(copyHand.cards.begin(), copyHand.cards.end());
		return copyHand.cards;
	}
	default:
	{
		return vector<Card>();
	}
	}
}

Hand parse_hand(list<string> cardDefs)
{
	Hand h;
	for (auto def : cardDefs) {
		h << stringToCard(def);
	}
	h.sortHand();
	return h;
}
