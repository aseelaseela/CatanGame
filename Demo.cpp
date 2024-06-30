//aseelzatmy3@gmail.com
//324885417
#include <iostream>
#include <stdexcept>
#include <vector>
#include "catan.hpp"
#include "player.hpp"

using namespace std;
using namespace ariel;

int main()
{
   string name1, name2, name3;

    cout << "Welcome to Catan!\nPlease insert your names:" << endl;
    cout << "Player 1, you will be orange. Enter your name:" << endl;
    cin >> name1;
    cout << "Player 2, you will be pink. Enter your name:" << endl;
    cin >> name2;
    cout << "Player 3, you will be green. Enter your name:" << endl;
    cin >> name3;

    // Create players with names and colors
    Player p1(name1, "\033[0;35m"); // Orange
    Player p2(name2, "\033[0;36m"); // Pink
    Player p3(name3, "\033[0;32m"); // Green

    // Create the game instance with players
    Catan catan(p1, p2, p3);

    // Starting phase: each player places two settlements and two roads
    cout << "\nStarting the game! Each player will place two settlements and two roads." << endl;

    // Starting of the game. Every player places two settlements and two roads.
    vector<Player>& players = catan.chooseStartingPlayer();   // should print the name of the starting player, assume it is Amit.
    for(unsigned int i=0; i<=2; i++){
        catan.printBoard();
        cout <<players[i].getName() << ", place your settlement #1" << endl;
        catan.placeSettlement(players[i]);
        catan.printBoard();
        cout <<players[i].getName() << ", place your road #1" << endl;
        catan.placeRoad(players[i]);
        catan.nextTurn();
    }
    catan.nextTurn();
    // Initialize loop variable
    unsigned int j = 3;

    while (j > 0) {
        unsigned int i = j - 1;

        catan.nextTurn();
        catan.printBoard();

        // Place settlement and road #2 for current player
        cout << players[i].getName() << ", place your settlement #2" << endl;
        catan.placeSettlement(players[i]);
        catan.printBoard();

        cout << players[i].getName() << ", place your road #2" << endl;
        catan.placeRoad(players[i]);
        catan.printBoard();

        catan.nextTurn();

        // Decrement j
        --j;
    }
    catan.printBoard();
    catan.nextTurn();
    int diceSum;
    unsigned int choice;
    while(!catan.checkWinner ()){
        cout << "It's your turn " << players[catan.getTurn()].getColor() << players[catan.getTurn()].getName() << "\033[0m" << endl;
        diceSum = catan.rollDice();
        choice = 10;
        while (choice != 9 && !catan.checkWinner()) {
            cout << "\n=== CATAN GAME ===" << endl;
            cout << "Choose your move:" << endl;
            cout << "1 - Build Settlement" << endl;
            cout << "2 - Build Road" << endl;
            cout << "3 - Buy Development Card" << endl;
            cout << "4 - Use Development Card" << endl;
            cout << "5 - Discard Cards" << endl;
            cout << "6 - Upgrade to City" << endl;
            cout << "7 - Trade with Bank" << endl;
            cout << "8 - Trade with Player" << endl;
            cout << "9 - End Turn" << endl;
            cout << "0 - Exit Game" << endl;
    
        // Input move choice
        cout << "Enter your choice: ";
        cin >> choice;

        // Process the chosen action
        switch (choice) {
            case 1:
                cout << "Where do you want to build your settlement? (Enter 0 to cancel)" << endl;
                catan.placeSettlement(players[catan.getTurn()]);
                break;
            case 2:
                cout << "Where do you want to build your road? (Enter 0 to cancel)" << endl;
                catan.placeRoad(players[catan.getTurn()]);
                break;
            case 3:
                 catan.buyDevelopmentCard(players[catan.getTurn()]);
                break;
            case 4:
                catan.useDevelopmentCard(players[catan.getTurn()]);
                break;
            case 5:
                cout << "Discarding Cards..." << endl;
                players[catan.getTurn()].displayCards();

            case 6:
                cout << "Choose a settlement to upgrade to a city. (Enter 0 to cancel)" << endl;
                catan.upgradeSettlement(players[catan.getTurn()]);
                break;
            case 7:
                players[catan.getTurn()].tradeWithBank();
                break;
            case 8:
               cout << "Choose a player to trade with. (Enter 0 to cancel)" << endl;
                catan.trade(players[catan.getTurn()]);
                break;
            case 9:
                cout << "Ending turn..." << endl;
                catan.nextTurn();
                break;
            case 0:
                cout << "Exiting game." << endl;
                return 0; // Exit the game loop and end the program
            default:
                cout << "Invalid choice. Please choose a valid option." << endl;
                break;
    }

        // Print the updated board after each action
        catan.printBoard();
    }
    }
        // End of game message
        cout << players[catan.getTurn()].getName() << " is the winner!!!\n";
}