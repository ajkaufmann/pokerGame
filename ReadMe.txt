Name: Andy Kaufmann
ID #: 441583

Lab 4: Multiple Card Games [I DID EXTRA CREDIT]

Design Notes:

My program does not differ substantially from the reccomended design.

A design choice I made for the seven card stud is to have a hand type associated with the hand if has a sign greater than one card.

A design choice I made was to leave one chip in the pot if spliting the pot leaves one chip left rather than allocating the chip to a certain player. (Let's call it a tip to the dealer!)

A design choice I made was that if the player gives no input or tries to change the game ot the same type the players in the game will not change.

Since the instructions do not say to use a dealer, I do not keep track of and use a dealer. The first player inputted will always be first in the game.

A design choice I made was implimenting my stop game method to write out all player files.

I continued my approach of using helper methods to accomplish smaller tasks within my code such using a method to manage the win results and to get allocate the pot properly.

Player files must be in the format Name: <playerName> Wins: <NumWins> Losses: <NumLosses> Chips: <NumChips> in order for my player constructor to work properly.

EXTRA CREDIT:

I created a TexasHoldEm game. To start a game, it is the same as any of the other games except use the gamename of TexasHoldEm.

Errors and Warnings:
An error I ran into when creating my program was with my sorting in the arrangeFlush() method. I was getting an error that I was using an invalid operator. I was trying to use the same_suit method to sort the cards. Originally in that method I was comparing the values using the == operator. I had to switch to using the < operator. In the end, my functionality of the program is the same so it has no impact on design. 

While building my program I saw various syntax errors. The reason I didnt run into any marjor errors was I was constantly compiling my code after each small change in order to be able to pinpoint where it was breaking down. 

Exit Codes:

NO_ERROR = 0;
INSTANCE_NOT_AVAILABLE = 1
GAME_ALREADY_STARTED = 2
UNKNOWN_GAME = 3
NO_GAME_IN_PROGRESS = 4
ALREADY_PLAYING = 5
INVALID_COMMAND_ARGUMENTS = 6
TOO_MANY_PLAYERS = 7
TOO_FEW_PLAYERS = 8

Throughout my code, other error values can be thrown but they are all caught and properly handled by various methods. The user should only have the above values returned to them.

Testing:

I tested the following inputs to see if my program could properly hand command line arguments:
	FiveCardDraw Andy Joe Allen - worked properly by starting a FiveCardDraw game.
	Five Andy Joe Allen - returned the error value of UNKNOWN_GAME.
	FiveCardDraw Joe - returned the INVALID_COMMAND_ARGUMENTS because there weren't enough players.
	SevenCardStud Andy Joe Allen - worked properly starting a SevenCardStud game.
	TexasHoldEm Andy Joe Allen - worked properly starting a SevenCardStud game. 


The following tests were all conducted with the command line arguments of FiveCardDraw Andy Joe Allen:
	Testing the ability to drop cards - Initially the cards were not being removed from the players hands. I overaloaded the << operator to get this to work properly.
	Testing the ability to leave a game - this worked successfully and writes to a file with the player name.
	Test ability to enter a game - initially this wasn't working but I debugged it properly by stepping through and realized that I need to use a holder value.
	Testing multiple rounds of the game -  this initially caused an issue because my dealer variable was just incrementing and eventually it caused an exception. To fix this, I mod the dealer variable by player size.

The following tests were all conducted with the command line arguments of SevenCardStud Andy Joe Allen:
	Testing the ability to leave a game - this worked successfully and writes to a file with the player name.
	Testing the ability to change the game after a single round of the game. - this worked switching to a new type of game.

I created a method called setHand() which allows me to set the hand contents of a player in my winManagement method. This was extremely helpful in the debugging process because it allowed me to articificially force edge cases with regards to hand contents. I ran through various combinations of hands and hand types to test handling ties, handling same hand type, and ensuring that my arrangeHand methods worked properly.

Throughout my process, I was using the debugger and walking through each method so I could see what was going on and ensuring that my code was properly handling cases, even if I didnt explicitly write them down.

Additional Notes:
I reused a lot of my code from previous assignments. So I am unsure if it is all 100% correct because I haven't gotten my labs back yet. 

Enclosed:
Card.h (Card struct declaration)
Deck.h (Deck class declaration)
Hand.h (Hand class declaration)
Parsing.h (Declaration of methods and enums needed to parse input files and determine hand type)
Game.h (Game abstract base class declaration)
PokerGame.h (PokerGame base class declaration derived through public inheritance from Game)
SevenCardStud.h (SevenCardStud class declaration derived through public inheritance from PokerGame)
FiveCardDraw.h (FiveCardDraw class declaration derived through public inheritance from PokerGame)
TexasHoldEm.h (TexamHoldEm class declaration derived through public inheritance from PoLerGame)
Player.h (Player declarations)

Card.cpp (Cards struct defintion)
Deck.cpp (Deck class definition)
Hand.cpp (Hand class definition)
Parsing.cpp (Definition of methods and enums)
Game.cpp (Game abstract base class defintion of some methods)
PokerGame.cpp (PokerGame base class defintion derived through public inheritance from Game)
SevenCardStud.cpp (SevenCardStud class definition derived through public inheritance from PokerGame)
FiveCardDraw.cpp (FiveCardDraw class definition derived through public inheritance from Game defintion)
TexasHoldEm.cpp (TexamHoldEm class definition derived through public inheritance from PoLerGame)
Player.cpp (Player defintion)

Lab03.cpp (main)