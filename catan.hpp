//aseelzatmy3@gmail.com
//324885417
#ifndef CATAN_HPP
#define CATAN_HPP

#include "player.hpp"
#include "developmentCard.hpp"
#include "board.hpp"

#include <vector>
#include <iostream>
#include <string>
#include <stack>
#include <memory>
#include <random>
#include <chrono>
#include <algorithm>

using std::stack;
using std::unique_ptr;

namespace ariel {
    class Catan {
    private:
        vector<Player> players;
        Board board;
        stack<unique_ptr<developmentCard>> devCards; 
        unsigned int turn = 0;

    public:
    //demo Benjamin Saldman
        Catan(Player& p1, Player& p2, Player& p3);
        ~Catan();
        // Getter method for devCards
        const stack<unique_ptr<developmentCard>>& getDevCards() const;
        Board& getBoard() ;
        const Board& getBoard() const ;
         // Method to set current player
        void setCurrentPlayer(size_t index);
        Player& getCurrentPlayer(); // Declaration of getCurrentPlayer method
        unsigned int getTurn();
        vector<Player>& chooseStartingPlayer();
        int rollDice();
        void nextTurn();
        bool placeSettlement(Player& p);
        bool upgradeSettlement(Player& p);
        bool trade(Player& p);
        bool placeRoad(Player& p);
        void printBoard();
        bool checkWinner ();
        void buyDevelopmentCard(Player& p);
        void useDevelopmentCard(Player& p);
        vector<Player>& getPlayers();
        void enforceDiscardingRule();
    };
}
#endif //CATAN_HPP