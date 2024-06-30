//aseelzatmy3@gmail.com
//324885417
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>
#include <iostream>
#include <string>

#include "board.hpp"
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::to_string;
using std::vector;

namespace ariel {
    class Player {
    private:
        string color;
        string name;
        int wool = 2;
        int ore = 0;
        int grain = 2;
        int wood = 4;
        int rock = 4;
        int knights = 0;
        int monopoly = 0;
        int yearOfPlenty = 0;
        int roadBuilding = 0;
        int roads = 0;
        int settlement=0;
        int city=0;
        int points = 0;

    public:
        Player();
        Player(string name, string color);
        ~Player();
        
        int getWood();
        int getRock();
        int getWool();
        int getOre();
        int getGrain();
        
        void addWood(int quantity);
        void addRock(int quantity);
        void addWool(int quantity);
        void addOre(int quantity);
        void addGrain(int quantity);
        void addPoint();
        void addMonopoly(int quantity);
        void addKnights(int quantity);
        void addYearOfPlenty(int quantity);
        void addRoadBuilding(int quantity);
        // Method to increment roads count
        void addRoads(int count);
        void addSettlement(int count);
        void addCity(int count);
        
        int getMonopoly();
        int getKnights();
        int getYearOfPlenty();
        int getRoadBuilding();
        
        string getName();
        string getColor();
        
        int getPoints();
        int getRoads();
        int getsettlement();
        int getCity();

        bool tradeWithPlayer(Player& to);
        bool tradeWithBank();
        void buildARoad();
        void buildASettlement();
        void upgradedCity();
        vector<int> discardHalfToBank();
        void printPoints();
        
        bool operator==(Player other);
        bool operator!=(Player other);

        // Method to set resources directly for testing trade function
        void setResources(int wool, int wood, int ore, int rock, int grain);
        void setDevelopmentCards(int monopoly, int knights, int yearOfPlenty, int roadBuilding);
        // Display cards held by the player
        void displayCards();

    };
}
#endif //PLAYER_CARD_HPP