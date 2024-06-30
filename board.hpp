//aseelzatmy3@gmail.com
//324885417
#ifndef BOARD_HPP
#define BOARD_HPP
#include "tile.hpp"

#include <vector>
#include <iostream>
#include <string>
#include <algorithm> 
#include <random>    
#include <chrono> 

using std::cout;
using std::endl;
using std::to_string;
using std::vector;
using std::string;

namespace ariel {
    class Board {
    private:
        vector<Tile> tiles;

    public:
        const vector<Tile>& getTilesboard() const;
        void initializeTile(Tile& tile, const string& type, unsigned int num, const vector<unsigned int>& neighbors, unsigned int tileIndex) ;
        Board();
        ~Board();
        void setOwner(unsigned int tile, string color);
        string getRoadColorBetweenTiles(unsigned int startTile, unsigned int endTile, string defaultRoadColor);
        void printBoard();
         // Getter methods for testing purposes
         Tile& getTile(unsigned int i);
        const vector<Tile>& getTiles() const;
        vector<Tile>& getMutableTiles();  // Non-const getter
    };
}
#endif //BOARD_HPP