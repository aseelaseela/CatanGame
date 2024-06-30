# CatanGame
Catan Board Class (Board)
The Board class in this Catan game implementation manages the game board consisting of hexagonal tiles. Each tile is represented by the Tile class, and the Board class initializes these tiles based on predefined resource types (Wood, Grain, Rock, Ore, Wool) and numbers (2-12), including a single Desert tile. The board is dynamically generated with randomized placement of these tiles and their connectivity defined by neighbor indices. The class provides methods to set and retrieve information about tiles, manage ownership of tiles by players, and print a visual representation of the board showing tiles, resource types, and roads between them. This implementation uses C++ with standard libraries for data structures and randomization.

Player Class
The Player class represents a player in Catan board game. It manages resources (wood, rock, wool, ore, grain), development cards (Knights, Monopoly, Year of Plenty, Road Building), settlements, cities, roads, and victory points for each player.

Constructor
Player(): Default constructor initializes with default values.
Player(string name, string color): Constructor to set player's name and color.
Getters
getWood(), getRock(), getWool(), getOre(), getGrain(): Retrieve resource counts.
getMonopoly(), getKnights(), getYearOfPlenty(), getRoadBuilding(): Retrieve development card counts.
getName(), getColor(): Retrieve player's name and color.
getPoints(), getRoads(), getSettlement(), getCity(): Retrieve player's victory points, roads, settlements, and cities.
Setters
setResources(int wool, int wood, int ore, int rock, int grain): Set resources directly for testing purposes.
setDevelopmentCards(int monopoly, int knights, int yearOfPlenty, int roadBuilding): Set development cards directly for testing purposes.
Resource Management
addWood(), addRock(), addWool(), addOre(), addGrain(): Add resources.
addRoads(int count), addSettlement(int count), addCity(int count): Increment roads, settlements, and cities.
addPoint(): Increment victory points.
Actions
buildARoad(): Build a road using wood and rock.
buildASettlement(): Build a settlement using wood, wool, grain, and rock.
upgradedCity(): Upgrade a settlement to a city using ore and grain.
tradeWithPlayer(Player& to): Initiate a trade with another player.
tradeWithBank(): Trade resources with the bank, adhering to specific trade rules.
discardHalfToBank(): Discard half of resources to the bank when holding 8 or more cards.
printPoints(): Display player's current victory points.
Other
operator==(), operator!=(): Equality operators for comparing players.
displayCards(): Display all held resources and development cards.
This class encapsulates the core functionalities and attributes of a player in the game, providing methods to manage resources, perform trades, and interact with the game board.


developmentCard Class
The developmentCard class serves as a base class for various development cards in Catan board game. Each development card is instantiated with a specific type, such as Knight, Monopoly, Year of Plenty, or Road Building, and can be played by a player during their turn to gain strategic advantages.

Constructor
developmentCard(string cardType): Initializes a development card with a specified type.
Destructor
~developmentCard(): Virtual destructor to ensure proper cleanup in derived classes.
Virtual Function
virtual void playCard(Player& p, Catan& c): Pure virtual function to be overridden in derived classes. This function defines the specific effect of the development card when played by a player within the game context.
This base class encapsulates the fundamental attributes and behaviors of development cards, allowing for specific implementations of card effects in derived classes. Additional derived classes would extend this base functionality to implement unique actions when cards are played during gameplay.

RoadBuilding Class
The RoadBuilding class represents a development card in a simplified implementation of the Catan board game. When played, this card allows a player to immediately place two roads on the game board, enhancing their ability to expand and connect their settlements.

Constructor
RoadBuilding(): Initializes the RoadBuilding card, inheriting from the developmentCard base class.
Functions
playCard(Player& p, Catan& c): Overrides the playCard method from the base class. This function checks if the player has sufficient resources and available road slots to place two roads consecutively. It interacts with the Player and Catan classes to deduct resources, attempt road placement, and handle any resource reversion if placement fails. Finally, it decreases the player's count of Road Building cards by 1 after use.
This implementation ensures that players can strategically use the Road Building card to expand their road network effectively in the game, adhering to the rules and limitations specified within the Catan board game mechanics.

Monopoly Class
The Monopoly class represents a development card in a simplified implementation of the Catan board game. When played, this card allows a player to monopolize a chosen resource, taking all units of that resource from every other player in the game.

Constructor
Monopoly(): Initializes the Monopoly card, inheriting from the developmentCard base class.
Functions
playCard(Player& p, Catan& c): Overrides the playCard method from the base class. This function prompts the player (p) to choose a resource (wool, wood, rock, ore, or grain) to monopolize. It then iterates through all players in the game (c.getPlayers()), excluding the current player (p), and transfers all units of the chosen resource from each other player to the current player (p). After executing the monopoly, it decreases the player's count of Monopoly cards by 1.
This implementation ensures that players can strategically use the Monopoly card to gain a significant advantage by acquiring a large quantity of a specific resource, potentially disrupting other players' resource management and development plans in the game.


VictoryPoint Class
The VictoryPoint class represents a development card in a simplified implementation of the Catan board game. When played, this card awards the player with an additional victory point.

Constructor
VictoryPoint(): Initializes the Victory Point card, inheriting from the developmentCard base class.
Functions
playCard(Player& p, Catan& c): Overrides the playCard method from the base class. This function adds 1 victory point to the player (p) who plays the card. It also outputs a message confirming the successful play of the Victory Point card and notifies the player about the increase in their victory points.
This implementation ensures that players can accumulate victory points through strategic use of the Victory Point card, contributing to their progress towards winning the game.


YearOfPlenty Class
The YearOfPlenty class represents a development card in a simplified implementation of the Catan board game. When played, this card allows the player to choose and receive two units of any one of the five resources available in the game.

Constructor
YearOfPlenty(): Initializes the Year of Plenty card, inheriting from the developmentCard base class.
Functions
playCard(Player& p, Catan& c): Overrides the playCard method from the base class. This function prompts the player (p) to choose a resource from a predefined list (Wood, Rock, Wool, Ore, Grain). Upon selection, it adds 2 units of the chosen resource to the player's inventory. The function also reduces the player's Year of Plenty card count by 1 and provides feedback on the resource received and the updated card count.
This implementation enhances player strategy by enabling them to acquire critical resources, aiding in their development and expansion within the game of Catan.

Knight Class
The Knight class represents a development card in a simplified implementation of the Catan board game. When played, this card increases the player's count of knights by 1. Knights are important in Catan for gaining the largest army bonus, a crucial victory point condition.

Constructor
Knight(): Initializes the Knight card, inheriting from the developmentCard base class.
Functions
playCard(Player& p, Catan& c): Overrides the playCard method from the base class. This function increments the player's count of knights by 1 and outputs a message confirming the action.
This implementation allows players to strategically build towards gaining the largest army, enhancing their path to victory in the game of Catan.


Tile Class
The Tile class represents a tile on the game board in a simplified implementation of the Catan board game. Each tile can hold various resources and is connected to neighboring tiles, forming the basic structure of the game board.

Constructors and Destructor
Tile(): Default constructor initializes the tile without specific attributes.
Tile(unsigned int id): Constructor initializes the tile with a unique identifier (id) and sets default values for other member variables.
~Tile(): Destructor cleans up resources allocated by the tile.
Member Variables
resourceTypes: Stores types of resources available at the tile.
resourceNumbers: Stores numbers associated with resources, typically used for dice roll results.
neighbors: Stores IDs of neighboring tiles.
roads: Stores owners of roads connected to this tile.
tileOwner: Stores the owner of the tile.
tileID: Unique identifier for the tile.
Member Functions
addInformation: Sets all essential information (resource types, numbers, neighbors, and ID) for the tile.
getNeighboringTiles: Returns a vector of neighboring tile IDs.
getRoads: Returns a vector of road owners connected to the tile.
setOwner: Sets the owner of the tile.
getOwner: Retrieves the owner of the tile.
setRoadOwner: Sets the owner of a specific road connected to the tile.
getRoadOwner: Retrieves the owner of a specific road.
getResourceType: Retrieves the type of resource at a specific index.
determineResourceByDiceRoll: Determines which resource (if any) matches a given dice roll result.
operator<<: Overloaded output operator to print the tile's details.
operator==: Overloaded equality operator to compare two tiles based on their IDs.
closeTo: Checks if two tiles are neighboring each other based on their IDs.
This class forms the fundamental building block for managing tiles and their interactions on the Catan game board, facilitating resource distribution, ownership tracking, and connectivity between tiles.

Catan Class (Catan.hpp, Catan.cpp)

The Catan class represents a simplified implementation of the board game Catan. It manages the game state, including players, the game board, development cards, and game mechanics.

Constructor and Destructor

Constructor: Initializes the game with three players (p1, p2, p3), sets up the board, and shuffles development cards.
Destructor: Currently empty; can be extended for cleanup if needed.
Member Variables

players: Vector storing instances of Player representing the game's participants.
board: Instance of Board representing the game board.
devCards: Stack of unique_ptr to developmentCard, containing shuffled development cards.
turn: Tracks the current player's turn.
Public Member Functions

chooseStartingPlayer(): Randomly shuffles players to determine starting order.
rollDice(): Simulates dice rolling and allocates resources to players based on board configuration.
nextTurn(): Moves to the next player's turn and announces it.
placeSettlement(Player& p): Allows a player to place a settlement on the board.
upgradeSettlement(Player& p): Upgrades a settlement to a city for a player.
trade(Player& p): Initiates a trade between the current player and another player.
placeRoad(Player& p): Allows a player to place a road on the board.
printBoard(): Prints the current state of the game board.
checkWinner(): Checks if any player has won based on victory conditions.
buyDevelopmentCard(Player& p): Allows a player to purchase a development card if resources permit.
useDevelopmentCard(Player& p): Allows a player to use a development card during their turn.
enforceDiscardingRule(): Checks and enforces the rule requiring players with excess cards to discard.
Private Member Functions

setCurrentPlayer(size_t index): Sets the current player based on the index provided.
getCurrentPlayer(): Retrieves the current player object.
getDevCards(), getBoard(): Getter methods for devCards and board.
The Catan class encapsulates the core gameplay logic, providing methods for player actions, resource management, and game progression. It serves as the main interface for controlling and interacting with the game state.

The demo.cpp file demonstrates a simple implementation of the popular board game Catan in C++. It begins by prompting three players to enter their names and assigns them respective colors (orange, pink, and green). The game progresses through phases where each player places two settlements and two roads on the board. Players take turns rolling dice, making decisions such as building settlements, roads, cities, buying development cards, and engaging in trade with both the bank and other players. The game continues until one player achieves victory conditions, signaling the end of the game.


Certainly! Here's a formal description for your README file:

Test Suite (test.cpp) for Catan Game Implementation

The test.cpp file comprises a comprehensive suite of unit tests designed to validate the functionality of every key feature within the Catan game implementation. Utilizing the Doctest testing framework (doctest.h), each test case rigorously examines various aspects of the game, including player interactions, resource management, trading mechanics, board setup, and adherence to game rules. Mock input and output streams are employed to simulate user interactions, ensuring thorough testing of both expected and edge-case scenarios. By leveraging Doctest's capabilities, the testing suite ensures the robustness, reliability, and correctness of the Catan game's core functionalities.

This project includes a Makefile (Makefile) that facilitates building and running the Catan game implementation. Follow these steps to compile and execute the program:
Ensure you have clang++ installed on your system.
The project requires C++14 standard compliance.
Steps to Compile and Run
Compile the Code:
Open a terminal window and navigate to the directory containing the Makefile and source files (*.cpp).
$ make demo
This command compiles the main executable demo using the C++ source files specified in the Makefile.
Run the Game:
Once compiled successfully, run the game by executing:
$ ./demo
This command starts the Catan game.

Additional Commands
Testing:
To compile and run tests, use:
$ make test
$ ./test
This command compiles and runs the test suite, ensuring the functionality of the game's components.
Cleaning Up
Remove compiled object files using:
$ make clean
This command deletes all .o files generated during compilation.

This project was created by Aseel Ahmad.














