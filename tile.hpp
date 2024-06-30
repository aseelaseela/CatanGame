//aseelzatmy3@gmail.com
//324885417
#ifndef TILE_H
#define TILE_H

#include <iostream>
#include <vector>
#include <string>

using std::cout;
using std::endl;
using std::to_string;
using std::vector;
using std::string;

namespace ariel {

    // Declaration of the Tile class
    class Tile {
    private:
        // Private member variables
        vector<string> resourceTypes;         // Types of resources available at the tile
        vector<unsigned int> resourceNumbers; // Numbers associated with resources
        vector<unsigned int> neighbors;       // Neighboring tiles' IDs
        vector<string> roads;                 // Owners of roads connected to this tile
        string tileOwner = "";                // Owner of the tile
        unsigned int tileID;                  // Unique identifier for the tile
        
    public:
        // Constructor and Destructor
        Tile();                               // Constructor
        ~Tile();                              // Destructor
        // Constructor with ID
        Tile(unsigned int id);

        // Getter methods
        vector<unsigned int> getNeighboringTiles(); // Returns the list of neighbors
        vector<string> getRoads();                  // Returns the list of roads

        // Method to add information to the tile
        void addInformation(vector<string> types, vector<unsigned int> numbers, vector<unsigned int> neighbors, unsigned int id);

        // Methods to set and get the owner of the tile
        void setOwner(string ownerColor);
        string getOwner();

        // Methods to set and get the owner of a specific road
        void setRoadOwner(string ownerColor, unsigned int roadIndex);
        string getRoadOwner(unsigned int roadIndex);

        // Method to get the type of resource at a specific place
        string getResourceType(unsigned int index);

        // Method to determine the resource based on dice roll result
        string determineResourceByDiceRoll(int result);

        // Overloaded output operator to print Tile details
        friend std::ostream& operator<<(std::ostream& os, Tile& t);

        // Overloaded equality operator to compare two tiles
        bool operator==(Tile other);

        // Method to determine if two tiles are close to each other
        bool closeTo(Tile other);
    };
}
#endif // TILE_H
