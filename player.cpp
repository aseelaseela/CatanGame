//aseelzatmy3@gmail.com
//324885417
#include "player.hpp"
#include <iostream>  // Include for std::cout and std::cin

using namespace ariel;

// Constructor
Player::Player() : name(""), color("") {}

Player::Player(string name, string color) : name(name), color(color) {}

// Destructor
Player::~Player() {}

// Getters
int Player::getWood() { return wood; }
int Player::getRock() { return rock; }
int Player::getWool() { return wool; }
int Player::getOre() { return ore; }
int Player::getGrain() { return grain; }

int Player::getMonopoly() { return monopoly; }
int Player::getKnights() { return knights; }
int Player::getYearOfPlenty() { return yearOfPlenty; }
int Player::getRoadBuilding() { return roadBuilding; }

string Player::getName() { return name; }
string Player::getColor() { return color; }

int Player::getPoints() { return points; }
int Player::getRoads() { return roads; }
int Player::getsettlement() { return settlement; }
int Player::getCity() { return city; }


// Add resources
void Player::addWood(int quantity) { wood += quantity; }
void Player::addRock(int quantity) { rock += quantity; }
void Player::addWool(int quantity) { wool += quantity; }
void Player::addOre(int quantity) { ore += quantity; }
void Player::addGrain(int quantity) { grain += quantity; }

// Add points and special cards
void Player::addPoint() { points++; }
void Player::addMonopoly(int quantity) { monopoly += quantity; }
void Player::addKnights(int quantity) { knights += quantity; }
void Player::addYearOfPlenty(int quantity) { yearOfPlenty += quantity; }
void Player::addRoadBuilding(int quantity) { roadBuilding += quantity; }

bool Player::tradeWithPlayer(Player& to) {
    // Check if trying to trade with themselves
    if (this == &to) {
        std::cout << "You cannot trade with yourself.\n";
        return false;
    }
    // Prompt current player for quantities they want to give
    int giveWool, giveWood, giveore, giveRock, giveGrain;
    int receiveWool, receiveWood, receiveore, receiveRock, receiveGrain;

    std::cout << "Enter the quantities of resources you want to give:\n";
    std::cout << "Grain: "; std::cin >> giveGrain;
    std::cout << "Wool: "; std::cin >> giveWool;
    std::cout << "Wood: "; std::cin >> giveWood;
    std::cout << "Rock: "; std::cin >> giveRock;
    std::cout << "ore: "; std::cin >> giveore;

    // Check if the current player has enough resources to give
    if (wool < giveWool || wood < giveWood || ore < giveore || rock < giveRock || grain < giveGrain) {
        std::cout << color << " (" << name  << "), you don't have enough resources to make this trade.\n";
        return false;
    }
    
    std::cout << "Enter the quantities of resources you want to receive:\n";
    std::cout << "Wool: "; std::cin >> receiveWool;
    std::cout << "Wood: "; std::cin >> receiveWood;
    std::cout << "ore: "; std::cin >> receiveore;
    std::cout << "Rock: "; std::cin >> receiveRock;
    std::cout << "grain: "; std::cin >> receiveGrain;

    // Check if the other player has enough resources to give
    if (to.getWool() < receiveWool || to.getWood() < receiveWood || to.getOre() < receiveore || to.getRock() < receiveRock || to.getGrain() < receiveGrain) {
        std::cout << to.getColor() << " (" << to.getName() << ") doesn't have enough resources to make this trade.\n";
        return false;
    }
    // Ensure no resource is traded in both directions
    if ((giveWool > 0 && receiveWool > 0) || (giveWood > 0 && receiveWood > 0) || 
        (giveore > 0 && receiveore > 0) || (giveRock > 0 && receiveRock > 0) || 
        (giveGrain > 0 && receiveGrain > 0)) {
        std::cout << "You cannot trade the same type of resource in both directions.\n";
        return false;
    }
    // Present the trade proposal to the other player
    std::cout << "Trade Proposal:\n";
    std::cout << color << "(" << name << ") gives: " << giveWool << " Wool, " << giveWood << " Wood, " << giveore << " ore, " << giveRock << " Rock, " << giveGrain << " grain\n";
    std::cout << to.getColor() <<  "(" << to.getName() << ") receives: " << receiveWool << " Wool, " << receiveWood << " Wood, " << receiveore << " ore, " << receiveRock << " Rock, " << receiveGrain << " grain\n"<< "\033[0m";
    std::cout << "Does" << to.getColor() << "(" << to.getName() << ")" << "\033[0m" << " accept this trade? (yes/no): ";
    std::string response;
    std::cin >> response;

    if (response != "yes") {
        std::cout << "Trade declined.\n";
        return false;
    }

    // Execute the trade
    wool -= giveWool;
    wood -= giveWood;
    ore -= giveore;
    rock -= giveRock;
    grain -= giveGrain;
    wool += receiveWool;
    wood += receiveWood;
    ore += receiveore;
    rock += receiveRock;
    grain += receiveGrain;
    to.addWool(giveWool);
    to.addWood(giveWood);
    to.addOre(giveore);
    to.addRock(giveRock);
    to.addGrain(giveGrain);
    to.addWool(-receiveWool);
    to.addWood(-receiveWood);
    to.addOre(-receiveore);
    to.addRock(-receiveRock);
    to.addGrain(-receiveGrain);

    std::cout << "Trade successful.\n";
    return true;
}
 // Method to increment roads count
    void Player::addRoads(int count) {
        roads += count;
    }
    void Player::addSettlement(int count) {
        settlement += count;
    }
    void Player::addCity(int count) {
        city += count;
    }
// Implement the setResources method for tests 
void Player::setResources(int wool, int wood, int ore, int rock, int grain) {
    this->wool = wool;
    this->wood = wood;
    this->ore = ore;
    this->rock = rock;
    this->grain = grain;
}
// Implement the setDevelopmentCards method for tests 
void Player::setDevelopmentCards(int monopoly, int knights, int yearOfPlenty, int roadBuilding) {
    this->monopoly = monopoly;
    this->knights = knights;
    this->yearOfPlenty = yearOfPlenty;
    this->roadBuilding = roadBuilding;
}
// Trade with the bank
bool Player::tradeWithBank() {
    // Prompt current player for quantities they want to give
    int giveWool, giveWood, giveore, giveRock, givegrain;
    int receiveWool, receiveWood, receiveore, receiveRock, receivegrain;

    std::cout << "Enter the quantities of resources you want to give:\n";
    std::cout << "Wool: "; std::cin >> giveWool;
    std::cout << "Wood: "; std::cin >> giveWood;
    std::cout << "ore: "; std::cin >> giveore;
    std::cout << "Rock: "; std::cin >> giveRock;
    std::cout << "grain: "; std::cin >> givegrain;

    // Check if the current player has enough resources to give
    if (wool < giveWool || wood < giveWood || ore < giveore || rock < giveRock || grain < givegrain) {
        std::cout << color << " (" << name  << "), you don't have enough resources to make this trade.\n";
        return false;
    }
     // Check if each amount of resource to give is divisible by 4
    if (giveWool % 4 != 0 || giveWood % 4 != 0 || giveore % 4 != 0 || giveRock % 4 != 0 || givegrain % 4 != 0) {
        std::cout << "You can only trade resources in quantities divisible by 4.\n";
        return false;
    }
    std::cout << "Enter the quantities of resources you want to receive:\n";
    std::cout << "Wool: "; std::cin >> receiveWool;
    std::cout << "Wood: "; std::cin >> receiveWood;
    std::cout << "ore: "; std::cin >> receiveore;
    std::cout << "Rock: "; std::cin >> receiveRock;
    std::cout << "grain: "; std::cin >> receivegrain;
    // Calculate total resources given and received
    int totalGive = (giveWool + giveWood + giveore + giveRock + givegrain)/4;
    int totalReceive = receiveWool + receiveWood + receiveore + receiveRock + receivegrain;

    // Verify if total resources given match total resources received
    if (totalGive != totalReceive) {
        std::cout << "Total resources to give (" << totalGive << ") must match total resources to receive (" << totalReceive << ").\n";
        return false;
    }
    // Execute the trade
    wool -= giveWool;
    wood -= giveWood;
    ore -= giveore;
    rock -= giveRock;
    grain -= givegrain;
    wool += receiveWool;
    wood += receiveWood;
    ore += receiveore;
    rock += receiveRock;
    grain += receivegrain;
    std::cout << "Trade with the bank successful.\n";
    return true;
}

// Build a road
void Player::buildARoad() {
    if (roads >= 15) {
        std::cout << "You have reached the maximum limit of 15 roads.\n";
        return;
    }
    if (wood > 0 && rock > 0) {
        wood--;
        rock--;
        roads++;
    }
    else {
        std::cout << "Insufficient resources to place a roads.\n";
    }
}

// Build a settlement
void Player::buildASettlement() {
    if (settlement >= 5) {
        std::cout << "You have reached the maximum limit of 5 settlements.\n";
        return;
    }
    if (wood > 0 && wool > 0 && grain > 0 && rock > 0) {
        wood--;
        wool--;
        grain--;
        rock--;
        settlement++;
        points++;
        std::cout << "Settlement placed successfully. You now have " << settlement << " settlements.\n";
    }
    else {
        std::cout << "Insufficient resources to place a Settlement.\n";
    }
}

// Upgrade a settlement to a city
void Player::upgradedCity() {
    if (city >= 4) {
        std::cout << "You have reached the maximum limit of 4 cities.\n";
        return;
    }

    if (ore >= 3 && grain >= 2) {
        ore -= 3;
        grain -= 2;
        city++;
        points++;
        std::cout << "City upgraded successfully. You now have " << city << " cities.\n";
    }
    else {
        std::cout << "Insufficient resources to upgrade city.\n";
    }
 }
        vector<int> Player::discardHalfToBank() {
             std::vector<int> discardedResources = {0, 0, 0, 0, 0}; // wool, wood, ore, rock, grain
            int totalResources = wool + wood + ore + rock + grain;

            if (totalResources >= 8) {
                int discardCount = totalResources / 2;
                cout << "You need to discard " << discardCount << " cards. Please choose the resources to discard:\n";
                
                while (discardCount > 0) {
                    cout << "1. Wool (" << wool << ")\n";
                    cout << "2. Wood (" << wood << ")\n";
                    cout << "3. Ore (" << ore << ")\n";
                    cout << "4. Rock (" << rock << ")\n";
                    cout << "5. Grain (" << grain << ")\n";
                    cout << "Enter the number of the resource to discard: ";
                    int choice;
                    cin >> choice;

                    switch (choice) {
                        case 1:
                            if (wool > 0) {
                                wool--;
                                discardedResources[0]++;
                                discardCount--;
                            } else {
                                cout << "You don't have enough wool to discard.\n";
                            }
                            break;
                        case 2:
                            if (wood > 0) {
                                wood--;
                                discardedResources[1]++;
                                discardCount--;
                            } else {
                                cout << "You don't have enough wood to discard.\n";
                            }
                            break;
                        case 3:
                            if (ore > 0) {
                                ore--;
                                discardedResources[2]++;
                                discardCount--;
                            } else {
                                cout << "You don't have enough ore to discard.\n";
                            }
                            break;
                        case 4:
                            if (rock > 0) {
                                rock--;
                                discardedResources[3]++;
                                discardCount--;
                            } else {
                                cout << "You don't have enough rock to discard.\n";
                            }
                            break;
                        case 5:
                            if (grain > 0) {
                                grain--;
                                discardedResources[4]++;
                                discardCount--;
                            } else {
                                cout << "You don't have enough grain to discard.\n";
                            }
                            break;
                        default:
                            cout << "Invalid choice. Please try again.\n";
                            break;
                    }
                }
            }
            return discardedResources;
        }

// Print player points
void Player::printPoints() {
    cout << "Player " << name << " has " << points << " points." << endl;
}

// Equality operators
bool Player::operator==(Player other) {
    return (name == other.name && color == other.color);
}

bool Player::operator!=(Player other) {
    return !(*this == other);
}
 void Player::displayCards() {
        cout << "Resources:" << endl;
        cout << "Wood: " << wood << endl;
        cout << "Rock: " << rock << endl;
        cout << "Wool: " << wool << endl;
        cout << "Ore: " << ore << endl;
        cout << "Grain: " << grain << endl;

        cout << "Development Cards:" << endl;
        cout << "Knights: " << knights << endl;
        cout << "Monopoly: " << monopoly << endl;
        cout << "Year of Plenty: " << yearOfPlenty << endl;
        cout << "Road Building: " << roadBuilding << endl;
    }