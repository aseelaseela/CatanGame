//aseelzatmy3@gmail.com
//324885417
#include "catan.hpp"
#include "Monopoly.hpp"
#include "YearOfPlenty.hpp"
#include "RoadBuilding.hpp"
#include "VictoryPoint.hpp"
#include "Knight.hpp"

#define FALSE 0
#define TRUE 1
using std::make_unique;
using namespace std;

namespace ariel {

    Catan::Catan(Player& p1, Player& p2, Player& p3) {
    players.push_back(p1);
    players.push_back(p2);
    players.push_back(p3);

    // Initialize the development cards
    vector<unique_ptr<developmentCard>> devcard_vector;
    
    // Populate the vector with development cards
    for (int i = 0; i < 5; ++i) {
        devcard_vector.push_back(make_unique<VictoryPoint>());
    }
    for (int i = 0; i < 14; ++i) {
        devcard_vector.push_back(make_unique<Knight>());
    }
    devcard_vector.push_back(make_unique<Monopoly>());
    devcard_vector.push_back(make_unique<Monopoly>());
    devcard_vector.push_back(make_unique<YearOfPlenty>());
    devcard_vector.push_back(make_unique<YearOfPlenty>());
    devcard_vector.push_back(make_unique<RoadBuilding>());
    devcard_vector.push_back(make_unique<RoadBuilding>());

    // Shuffle the vector
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    shuffle(devcard_vector.begin(), devcard_vector.end(), default_random_engine(seed));

    // Transfer the shuffled cards to the devcards stack
    while (!devcard_vector.empty()) {
        devCards.push(move(devcard_vector.back()));
        devcard_vector.pop_back();
    }
    // Transfer the shuffled cards to the devcards stack using a for loop
    // for (auto it = devcard_vector.rbegin(); it != devcard_vector.rend(); ++it) {
    //     devcards.push(move(*it));
    // }

    // Initialize the board
    board=Board();
}

    Catan::~Catan() {
    // Destructor implementation (if needed)
    }
    
    std::vector<Player>& Catan::chooseStartingPlayer() {
    // Obtain a time-based seed
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    // Initialize a random engine with the seed
    std::default_random_engine engine(seed);

    // Shuffle the players vector
    std::shuffle(players.begin(), players.end(), engine);

    // Print the new order of players
    cout << "The starting player order is:" << endl;
    for (size_t i = 0; i < players.size(); ++i) {
        cout << players[i].getColor() << i + 1 << ": " << players[i].getName() << "\033[0m" << endl;
    }
    turn=0;
    // Return the shuffled vector
    return players;
}

    vector<Player>& Catan::getPlayers() {
        return players; 
    }
    unsigned int Catan::getTurn(){ 
        return turn; 
    }

    void Catan::nextTurn() {
        // Update turn index
        turn = (turn + 1) % players.size();  // Ensure the turn index wraps around based on the number of players

        // Print a message indicating the next player's turn
        std::cout << "It's now " << players[turn].getColor() << players[turn].getName() << "\033[0m" << "'s turn." << std::endl;
    }
Player& Catan::getCurrentPlayer() {
        if (turn >= players.size()) {
            throw std::out_of_range("Turn index out of range");
        }
        return players[turn];
    }
    
int Catan::rollDice() {
    // Obtain a time-based seed
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    // Initialize random number generator with the time-based seed
    std::default_random_engine engine(seed);
    std::uniform_int_distribution<int> distribution(1, 6);  // Dice range: 1 to 6

    // Roll two six-sided dice
    int die1 = distribution(engine);
    int die2 = distribution(engine);
    int sum = die1 + die2;

    // Print the result of the dice roll
    std::cout << "Rolled dice: " << die1 << " + " << die2 << " = " << sum << std::endl;

    // Allocate resources based on the roll
    // Check board spots for matching dice number and allocate resources
    for (unsigned int spot = 1; spot <= 54; ++spot) {
        std::string resourceType = board.getTile(spot).determineResourceByDiceRoll(sum); 

        if (resourceType != "0") {
            // Iterate through all players
            for (unsigned int i=0 ; i<players.size() ; i++) {
                // Check if player owns the spot
                if (board.getTile(spot).getOwner() == players[i].getColor()) {
                    // Allocate resource to the player
                    if(resourceType == "Grain") 
                        players[i].addGrain(1);
                    if(resourceType == "Rock") 
                        players[i].addRock(1);
                    if(resourceType == "Wool") 
                        players[i].addWool(1);
                    if(resourceType == "Wood") 
                        players[i].addWood(1);
                    if(resourceType == "ore") 
                        players[i].addOre(1);              
            }
        }
      }
    }
    // Return the sum of the dice roll
    return sum;
}
void Catan::setCurrentPlayer(size_t index) {
            if (index < players.size()) {
                turn = index;
            } else {
                // Handle index out of bounds error (if needed)
                // Alternatively, you can throw an exception or handle it based on your design
                // Example:
                throw std::out_of_range("Index out of bounds");
            }
        }
    bool Catan::placeSettlement(Player& p) {
    // Check if it's the player's turn
    if (players[turn] != p) {
        std::cout << "It's not your turn to place a settlement.\n";
        return false;
    }

    // Prompt the player to choose a spot
    std::cout << "Player " << p.getColor() << p.getName() << " choose a spot to place your settlement (1-54).\n" << "\033[0m";
    unsigned int spotIndex;

    while (true) {
        std::cin >> spotIndex;

        // Validate the spot index
        if (spotIndex < 1 || spotIndex > 54) {
            std::cout << "Invalid spot index. Choose a spot between 1 and 54.\n";
            continue;
        }

        // Check if the spot is already occupied
        if (board.getTile(spotIndex).getOwner() != "") {
            std::cout << "There is already a settlement at spot " << spotIndex << ". Choose another spot.\n";
            continue;
        }

        // Check neighbors for settlements
        bool canPlace = true;
        std::vector<unsigned int> neighbors = board.getTile(spotIndex).getNeighboringTiles();
        for (unsigned int neighbor : neighbors) {
            if (board.getTile(neighbor).getOwner() != "") {
                std::cout << "You cannot place a settlement adjacent to another settlement.\n";
                canPlace = false;
                break;
            }
        }

        if (!canPlace) {
            std::cout << "Choose another spot.\n";
            continue;
        }

        // Place the settlement on the board
        p.buildASettlement();
        board.setOwner(spotIndex, p.getColor());
        p.addPoint();

        std::cout << "Settlement placed successfully at spot " << spotIndex << "!\n";
        break; // Exit the loop once settlement is successfully placed
    }

    return true;
}

        const stack<unique_ptr<developmentCard>>& Catan::getDevCards() const {
            return devCards;
        }
        Board& Catan::getBoard() {
            return board;
        }

        const Board& Catan::getBoard() const {
            return board;
        }
    bool Catan::upgradeSettlement(Player& p) {
    // Check if it's the player's turn
    if (players[turn] != p) {
        std::cout << "It's not your turn to upgrade a settlement to a city.\n";
        return false;
    }

    // Prompt the player to choose a spot
    std::cout << "Player " << p.getColor() << ", choose a spot to upgrade your settlement to a city (1-54): ";
    unsigned int spotIndex;
    std::cin >> spotIndex;

    // Validate the spot index
    while (spotIndex < 1 || spotIndex > 54) {
        std::cout << "Invalid spot index. Choose a spot between 1 and 54.\n";
        std::cout << "Player " << p.getColor() << ", choose a spot to upgrade your settlement to a city (1-54): ";
        std::cin >> spotIndex;
    }

    // Check if the spot contains the player's settlement
    if (board.getTile(spotIndex).getOwner() != p.getColor()) {
        std::cout << "You do not own a settlement at spot " << spotIndex << ".\n";
        return false;
    }

    // Perform the upgrade
    p.upgradedCity();  // Deduct resources and upgrade settlement to city
    board.setOwner(spotIndex, p.getColor().replace(2, 2, "1;"));  // Update board state
    p.addPoint(); // Update player's points

    // Print success message
    std::cout << "Settlement at spot " << spotIndex << " upgraded to a city successfully!\n";
    return true;
}
void Catan::enforceDiscardingRule() {
        for (auto& player : players) {
            if (player.getWool() + player.getWood() + player.getOre() + player.getRock() + player.getGrain() >= 8) {
                std::vector<int> discardedResources = player.discardHalfToBank();
            }
        }
    }
bool Catan::trade(Player& p) {
    std::string tradePartnerName;
    Player* tradePartner = nullptr;
    std::cout << "Enter the name of the player you want to trade with: ";
    std::cin >> tradePartnerName;

    // Find the trade partner player by name
    for (auto& player : players) {
    if (player.getName() == tradePartnerName && player != p) {
        tradePartner = &player;
        break;
    }
    }
    // If trade partner is not found or trying to trade with self
    if (tradePartner == nullptr) {
        std::cout << "Invalid trade partner or cannot trade with yourself." << std::endl;
        return false;
    }
    if (tradePartner) {
    // Assuming p.trade expects a reference (ariel::Player&)
    if (p.tradeWithPlayer(*tradePartner)) {
        std::cout << "Successfully traded." << std::endl;
        return true;
    }
    }
        std::cout << " cannot trade ." << std::endl;
        return false;
}
 bool Catan::placeRoad(Player& p){
        if(players[turn] != p){
            cout << "It's not your turn to place a road.\n" << endl;
            return false;
        }
        unsigned int spotIndex1, spotIndex2;
        while(1){
            cin >> spotIndex1;
            cin >> spotIndex2;
            if(spotIndex1 == 0 || spotIndex2 == 0)
            { 
                return false; 
            }
            if(spotIndex1 < 1 || spotIndex2 < 1  || spotIndex1 > 54 || spotIndex2 > 54){
                cout << "Invalid spot indices. Choose spots between 1 and 54.\n" << endl;
                continue;
            }
            if(!board.getTile(spotIndex1).closeTo(board.getTile(spotIndex2))){
                std::cout << "Invalid road placement. Spots " << spotIndex1 << " and " << spotIndex2 << " are not adjacent.\n";
                continue;
            }
            bool canPlaceRoad = p.getColor() != board.getTile(spotIndex1).getOwner() && p.getColor() != board.getTile(spotIndex2).getOwner();
            bool fromValid = board.getTile(spotIndex1).getOwner()=="" || p.getColor() != board.getTile(spotIndex1).getOwner().replace(2, 2, "0;");
            bool toValid = board.getTile(spotIndex2).getOwner()=="" || p.getColor() != board.getTile(spotIndex2).getOwner().replace(2, 2, "0;");
            if(canPlaceRoad && fromValid && toValid){
                bool connectedToRoad = false;
                vector<string> roads = board.getTile(spotIndex1).getRoads();
                for(unsigned int i=0; i<roads.size(); i++)
                    if(roads[i] == p.getColor()) connectedToRoad = true; 
                
                roads = board.getTile(spotIndex2).getRoads();
                for(unsigned int i=0; i<roads.size(); i++)
                    if(roads[i] == p.getColor()) connectedToRoad = true; 
                
                if(!connectedToRoad){
                    cout << "Road placement invalid. You must connect to an existing road or settlement.\n"<< endl; 
                    continue;
                }
            }
            p.buildARoad();
            vector<unsigned int> neighborsIndex1 = board.getTile(spotIndex1).getNeighboringTiles();
            bool existingRoad = false;
            for(unsigned int i=0; i<neighborsIndex1.size(); i++){
                if(board.getTile(neighborsIndex1[i]) == board.getTile(spotIndex2)){
                    if(board.getTile(spotIndex1).getRoadOwner(i) != ""){
                        existingRoad = true;
                        break;
                    }
                    board.getTile(spotIndex1).setRoadOwner(p.getColor(), i);
                }
            }
            if(existingRoad){
                cout << "There is an existing Road" << endl;
                continue;
            }
            vector<unsigned int> neighborsIndex2 = board.getTile(spotIndex2).getNeighboringTiles();
            for(unsigned int i=0; i<neighborsIndex2.size(); i++){
                if(board.getTile(neighborsIndex2[i]) == board.getTile(spotIndex1)){
                    board.getTile(spotIndex2).setRoadOwner(p.getColor(), i);
                }
            }
            break;
        }
        return true;
    }
    
    
    void Catan::printBoard(){
        this->board.printBoard();
    }

    bool Catan::checkWinner () {
    // Initialize variables to track most roads and knights
    Player* mostRoadsPlayer = nullptr;
    Player* mostKnightsPlayer = nullptr;
    int maxRoads = 0;
    int maxKnights = 0;
    size_t mostRoadsPlayerIndex = 0; // Use size_t for indices
    size_t mostKnightsPlayerIndex = 0; // Use size_t for indices
    vector<int> points={players[0].getPoints(),players[1].getPoints(),players[2].getPoints()};

    // Iterate through players to count roads and knights
    for (size_t i = 0; i < players.size(); ++i) {
        int playerRoads = players[i].getRoads();
        int playerKnights = players[i].getKnights();

        // Check for most roads
        if (playerRoads > maxRoads) {
            maxRoads = playerRoads;
            mostRoadsPlayer = &players[i];
            mostRoadsPlayerIndex = i;
        }

        // Check for most knights
        if (playerKnights > maxKnights) {
            maxKnights = playerKnights;
            mostKnightsPlayer = &players[i];
            mostKnightsPlayerIndex = i;
        }
    }

    // Award bonus points if there's a clear leader in roads or knights
    bool bonusAwarded = false;

    // Bonus for roads
    if (mostRoadsPlayer && maxRoads > 0) {
        bool clearLeaderRoads = true;
        for (size_t i = 0; i < players.size(); ++i) {
            if (i != mostRoadsPlayerIndex && players[i].getRoads() == maxRoads) {
                clearLeaderRoads = false;
                break;
            }
        }
        if (clearLeaderRoads) {
            // Adjust bonus points for roads (example: +2 points)
            points[mostRoadsPlayerIndex] += 2;
            std::cout << "Bonus points awarded to " << mostRoadsPlayer->getName() << " for most roads.\n";
            bonusAwarded = true;
        }
    }

    // Bonus for knights
    if (mostKnightsPlayer && maxKnights > 0) {
        bool clearLeaderKnights = true;
        for (size_t i = 0; i < players.size(); ++i) {
            if (i != mostKnightsPlayerIndex && players[i].getKnights() == maxKnights) {
                clearLeaderKnights = false;
                break;
            }
        }
        if (clearLeaderKnights) {
            // Adjust bonus points for knights (example: +2 points)
            points[mostKnightsPlayerIndex] += 2;
            std::cout << "Bonus points awarded to " << mostKnightsPlayer->getName() << " for most knights.\n";
            bonusAwarded = true;
        }
    }

    return bonusAwarded;
}

    void Catan::buyDevelopmentCard(Player& p) {
    // Check if it's the player's turn
    if (players[turn] != p) {
        std::cout << "It's not your turn to buy a development card.\n";
        return;
    }
    if (devCards.empty())
    {
        std::cout << "No development cards available.\n";
        return;
    }
    
    // Check resource availability
    if (p.getGrain() < 1 || p.getWool() < 1 || p.getOre() < 1) {
        std::cout << "Insufficient resources to buy a development card.\n";
        return;
    }

    // Deduct resources
    p.addGrain(-1);
    p.addWool(-1);
    p.addOre(-1);

    // Generate a development card (example: random selection)
    std::vector<std::string> devCardTypes = {"Knight", "Year of Plenty", "Road Building", "Monopoly", "Victory Point"};
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(0, devCardTypes.size() - 1);
    std::string cardType = devCardTypes[static_cast<size_t>(distr(gen))];

    // Create the corresponding development card object
    developmentCard* newCard = nullptr;
    if (cardType == "Knight") {
        newCard = new Knight();
        p.addKnights(1);
        std::cout << "You bought a " << cardType << " development card.\n";
    } else if (cardType == "Year of Plenty") {
        newCard = new YearOfPlenty();
        p.addYearOfPlenty(1);
        std::cout << "You bought a " << cardType << " development card.\n";
    } else if (cardType == "Road Building") {
        newCard = new RoadBuilding();
        p.addRoadBuilding(1);
        std::cout << "You bought a " << cardType << " development card.\n";
    } else if (cardType == "Monopoly") {
        newCard = new Monopoly();
        p.addMonopoly(1);
        std::cout << "You bought a " << cardType << " development card.\n";
    } else if (cardType == "Victory Point") {
        newCard = new VictoryPoint();
        newCard->playCard(p,*this);
        std::cout << "You bought a " << cardType << " development card.\n";
    }else std::cout << "Error: Failed to create a development card.\n";
}

void Catan::useDevelopmentCard(Player& p) {
    std::cout << "Player " << p.getName() << ", choose a development card to use:\n";
    std::cout << "1. Knight\n";
    std::cout << "2. Year of Plenty\n";
    std::cout << "3. Road Building\n";
    std::cout << "4. Monopoly\n";
    int choice;
    std::cin >> choice;

    switch (choice) {
        case 1:
            if (p.getKnights()>0)
            {
                Knight().playCard(p,*this);
            }
            break;
        case 2:
            if (p.getYearOfPlenty()>0)
            {
                Monopoly().playCard(p,*this);
            }
            break;
        case 3:
            if (p.getRoadBuilding()>0)
            {
                Monopoly().playCard(p,*this);
            }
            break;
        case 4:
            if (p.getMonopoly()>0)
            {
                Monopoly().playCard(p,*this);
            }
            break;
        default:
            std::cout << "Invalid choice. No action taken.\n";
            return;
    }
    std::cout << "Development card used successfully.\n";
}


}