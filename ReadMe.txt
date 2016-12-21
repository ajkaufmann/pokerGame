Multiple Card Games

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
