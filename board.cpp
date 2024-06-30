//aseelzatmy3@gmail.com
//324885417
#include "board.hpp"
#include <random>
#include <chrono>
#include <ctime>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace ariel;
using std::vector;
using std::string;
using std::to_string;
using std::cout;
using std::endl;

namespace ariel {
void Board::initializeTile(Tile& Tile, const string& type, unsigned int num, const vector<unsigned int>& neighbors, unsigned int TileIndex) {
    Tile.addInformation({type}, {num}, neighbors, TileIndex);
}

Board::Board() {
    tiles = {
        Tile(), Tile(), Tile(),
        Tile(), Tile(), Tile(), Tile(),
        Tile(), Tile(), Tile(), Tile(),
        Tile(), Tile(), Tile(), Tile(), Tile(),
        Tile(), Tile(), Tile(), Tile(), Tile(),
        Tile(), Tile(), Tile(), Tile(), Tile(), Tile(),
        Tile(), Tile(), Tile(), Tile(), Tile(), Tile(),
        Tile(), Tile(), Tile(), Tile(), Tile(),
        Tile(), Tile(), Tile(), Tile(), Tile(),
        Tile(), Tile(), Tile(), Tile(),
        Tile(), Tile(), Tile(), Tile(),
        Tile(), Tile(), Tile()
    };
    vector<unsigned int> nums = {5, 2, 6, 3, 8, 10, 9, 12, 11, 4, 8, 10, 9, 4, 5, 6, 3, 11, 9, 7};
    vector<string> types = {"Wood", "Wood", "Wood", "Wood", "Grain", "Grain", "Grain", "Grain", "Rock", "Rock", "Rock", "Rock", "Ore", "Ore", "Ore", "Wool", "Wool", "Wool" , "Desert"};
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(types.begin(), types.end(), std::default_random_engine(seed));

    vector<vector<unsigned int>> neighborIndices = {
        {4, 5}, {5, 6}, {6, 7},
        {1, 8}, {1, 2, 9}, {2, 3, 10}, {3, 11},
        {4, 12, 13}, {13, 14, 5}, {14, 15, 6}, {15, 16, 7},
        {8, 17}, {8, 9, 18}, {9, 10, 19}, {10, 11, 20}, {11, 21},
        {12, 22, 23}, {23, 23, 13}, {24, 25, 14}, {25, 26, 15}, {26, 27, 16},
        {17, 28}, {17, 18, 29}, {18, 19, 30}, {19, 20, 31}, {20, 21, 32}, {21, 33},
        {34, 22}, {34, 35, 23}, {35, 36, 23}, {36, 37, 25}, {37, 38, 26}, {38, 27},
        {28, 39, 29}, {29, 30, 40}, {30, 31, 41}, {31, 32, 42}, {32, 33, 43},
        {44, 34}, {44, 45, 35}, {45, 46, 36}, {46, 47, 37}, {47, 38},
        {48, 39, 40}, {40, 41, 49}, {41, 42, 50}, {42, 43, 51},
        {52, 44}, {52, 53, 45}, {53, 54, 46}, {54, 47},
        {48, 49}, {49, 50}, {50, 51}
    };

    for (unsigned int i = 0; i < 54; ++i) {
        initializeTile(tiles[i], types[i % types.size()], nums[i % nums.size()], neighborIndices[i], i + 1);
    }
}
    Board::~Board(){}

    string Board::getRoadColorBetweenTiles(unsigned int startTile, unsigned int endTile, string defaultRoadColor) {
    // Check if the startTile and endTile are within valid bounds
    if (startTile < 1 || startTile > tiles.size() || endTile < 1 || endTile > tiles.size()) {
        return defaultRoadColor; // Return the roadColor if the indices are out of bounds
    }

    // Get the neighboring tiles of the start tile
    vector<unsigned int> neighboringTileIndices  = tiles[startTile].getNeighboringTiles();

    // Iterate over each neighboring tile to find a connection to the end tile
    for (unsigned int i = 0; i < neighboringTileIndices .size(); ++i) {
        if (tiles[neighboringTileIndices [i]-1] ==tiles[endTile]) {
            // If a connection is found, return the existing road owner with the new road color
            return tiles[startTile].getRoadOwner(i) + defaultRoadColor + "\033[0m";
        }
    }

    // If no connection is found, return the road color unchanged
    return defaultRoadColor;
}


    // Getter method for testing purposes
    const vector<Tile>& Board::getTilesboard() const{
        return tiles;
    }

    void Board::setOwner(unsigned int Tile, string color){
        this->tiles[Tile-1].setOwner(color);
    }    
    Tile& Board::getTile(unsigned int i){
        return tiles[i-1];
    }

void Board::printBoard(){
        cout << "************ CATAN BOARD ************\n       sea   sea   sea   sea   sea       \n"<< "\n            " << tiles[0] << tiles[1] << tiles[2] << 
        "\n           "<<getRoadColorBetweenTiles(0,3,"/   ")<<getRoadColorBetweenTiles(0,4,"\\   ")<<getRoadColorBetweenTiles(1,4,"/   ")<<getRoadColorBetweenTiles(1,5,"\\   ")<<getRoadColorBetweenTiles(2,5,"/   ")<<getRoadColorBetweenTiles(2,6,"\\   ") << "\n        " << tiles[3] << tiles[4] << tiles[5] << tiles[6] << 
        "\n         "<<getRoadColorBetweenTiles(3,7,"|")<<tiles[0].getResourceType(0)<<getRoadColorBetweenTiles(4,8,"|")<<tiles[1].getResourceType(0)<<getRoadColorBetweenTiles(5,9,"|")<<tiles[2].getResourceType(0)<<getRoadColorBetweenTiles(6,10,"|") << 
        "\n        " << tiles[7] << tiles[8] << tiles[9] << tiles[10] <<"\n       "<<getRoadColorBetweenTiles(7,11,"/    ")<<getRoadColorBetweenTiles(7,12,"\\  ")<<getRoadColorBetweenTiles(8,12,"/    ")<<getRoadColorBetweenTiles(8,13,"\\  ")<<getRoadColorBetweenTiles(9,13,"/    ")<<getRoadColorBetweenTiles(9,14,"\\  ")<<getRoadColorBetweenTiles(10,14,"/    ")<<getRoadColorBetweenTiles(10,15,"\\  ") << 
        "\n    " << tiles[11] << tiles[12] << tiles[13] << tiles[14] << tiles[15] <<"\n     "<<getRoadColorBetweenTiles(11,16,"|")<<tiles[7].getResourceType(0)<<getRoadColorBetweenTiles(12,17,"|")<<tiles[8].getResourceType(0)<<getRoadColorBetweenTiles(13,18,"|")<<tiles[9].getResourceType(0)<<getRoadColorBetweenTiles(14,19,"|")<<tiles[10].getResourceType(0)<<getRoadColorBetweenTiles(15,20,"|") << 
        "\n    " << tiles[16] << tiles[17] << tiles[18] << tiles[19] << tiles[20] <<"\n   "<<getRoadColorBetweenTiles(16,21,"/    ")<<getRoadColorBetweenTiles(16,22,"\\  ")<<getRoadColorBetweenTiles(17,22,"/    ")<<getRoadColorBetweenTiles(17,23,"\\  ")<<getRoadColorBetweenTiles(18,23,"/    ")<<getRoadColorBetweenTiles(18,24,"\\  ")<<getRoadColorBetweenTiles(19,24,"/    ")<<getRoadColorBetweenTiles(19,25,"\\  ")<<getRoadColorBetweenTiles(20,25,"/    ")<<getRoadColorBetweenTiles(20,26,"\\  ") << 
        "\n"<< tiles[21] << tiles[22] << tiles[23] << tiles[24] << tiles[25] << tiles[26] << "\n "<<getRoadColorBetweenTiles(21,27,"|")<<tiles[16].getResourceType(0)<<getRoadColorBetweenTiles(22,28,"|")<<tiles[17].getResourceType(0)<<getRoadColorBetweenTiles(23,29,"|")<<tiles[18].getResourceType(0)<<getRoadColorBetweenTiles(24,30,"|")<<tiles[19].getResourceType(0)<<getRoadColorBetweenTiles(25,31,"|")<<tiles[20].getResourceType(0)<<getRoadColorBetweenTiles(26,32,"|") << 
        "\n" <<tiles[27] << tiles[28] << tiles[29] << tiles[30] << tiles[31] << tiles[32] <<"\n   "<<getRoadColorBetweenTiles(27,33,"\\    ")<<getRoadColorBetweenTiles(28,33,"/  ")<<getRoadColorBetweenTiles(28,34,"\\    ")<<getRoadColorBetweenTiles(29,34,"/  ")<<getRoadColorBetweenTiles(29,35,"\\    ")<<getRoadColorBetweenTiles(30,35,"/  ")<<getRoadColorBetweenTiles(30,36,"\\    ")<<getRoadColorBetweenTiles(31,36,"/  ")<<getRoadColorBetweenTiles(31,37,"\\    ")<<getRoadColorBetweenTiles(32,37,"/  ") << 
        "\n    " << tiles[33] << tiles[34] << tiles[35] << tiles[36] << tiles[37] << "\n     "<<getRoadColorBetweenTiles(33,38,"|")<<tiles[28].getResourceType(0)<<getRoadColorBetweenTiles(34,39,"|")<<tiles[29].getResourceType(0)<<getRoadColorBetweenTiles(35,40,"|")<<tiles[30].getResourceType(0)<<getRoadColorBetweenTiles(36,41,"|")<<tiles[31].getResourceType(0)<<getRoadColorBetweenTiles(37,42,"|") << 
        "\n    " << tiles[38] << tiles[39] << tiles[40] << tiles[41] << tiles[42] << "\n       "<<getRoadColorBetweenTiles(38,43,"\\    ")<<getRoadColorBetweenTiles(39,43,"/  ")<<getRoadColorBetweenTiles(39,44,"\\    ")<<getRoadColorBetweenTiles(40,44,"/  ")<<getRoadColorBetweenTiles(40,45,"\\    ")<<getRoadColorBetweenTiles(41,45,"/  ")<<getRoadColorBetweenTiles(41,46,"\\    ")<<getRoadColorBetweenTiles(42,46,"/  ") <<
        "\n        " << tiles[43] << tiles[44] << tiles[45] << tiles[46] <<"\n         "<<getRoadColorBetweenTiles(43,47,"|")<<tiles[39].getResourceType(0)<<getRoadColorBetweenTiles(44,48,"|")<<tiles[40].getResourceType(0)<<getRoadColorBetweenTiles(45,49,"|")<<tiles[41].getResourceType(0)<<getRoadColorBetweenTiles(46,50,"|") <<
        "\n        " << tiles[47] << tiles[48] << tiles[49] << tiles[50] <<"\n           "<<getRoadColorBetweenTiles(47,51,"\\    ")<<getRoadColorBetweenTiles(48,51,"/  ")<<getRoadColorBetweenTiles(48,52,"\\    ")<<getRoadColorBetweenTiles(49,52,"/  ")<<getRoadColorBetweenTiles(49,53,"\\    ")<<getRoadColorBetweenTiles(50,53,"/  ") <<
        "\n            " << tiles[51] << tiles[52] << tiles[53] << "\n\n\n\n" << "\n       sea   sea   sea   sea   sea      \n " << endl;
    }

// Getter methods for testing purposes
const vector<Tile>& Board::getTiles() const {
    return tiles;
}

vector<Tile>& Board::getMutableTiles() {
    return tiles;
}
}