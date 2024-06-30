//aseelzatmy3@gmail.com
//324885417
#include "tile.hpp"

namespace ariel {
    // Constructor
    Tile::Tile() {
        // Initialize member variables if needed
    }
    Tile::Tile(unsigned int id) {
        tileID = id;
        // Initialize other member variables as needed based on id
        tileOwner = ""; // Initialize tileOwner as empty string or default owner
    }
    // Destructor
    Tile::~Tile() {
        // Clean up resources if needed
    }
    vector<unsigned int> Tile::getNeighboringTiles(){
         return neighbors; 
    }  
    vector<string> Tile::getRoads() {
         return roads;
    }
    string Tile::getRoadOwner(unsigned int roadIndex) {
        return roads[roadIndex];
    }
    string Tile::getOwner() { 
        return this->tileOwner; 
    }
    void Tile::setRoadOwner(string ownerColor, unsigned int roadIndex)
    {
        this->roads[roadIndex] = ownerColor; 
    }
    void Tile::setOwner(string ownerColor) {
        this->tileOwner = ownerColor; 
    }
    // Method to add information to the tile
    void Tile::addInformation(vector<string> resourceTypes, vector<unsigned int> resourceNumbers, vector<unsigned int> neighbors, unsigned int tileID) {
        this->resourceTypes = resourceTypes;
        this->resourceNumbers = resourceNumbers;
        this->neighbors = neighbors;
        this->tileID = tileID;
        this->roads.resize(neighbors.size(), ""); // Initialize roads with empty owners
    }   
    string Tile::getResourceType(unsigned int index) {
      // Check if the provided index is within the valid range
      if (index >= resourceTypes.size() || index >= resourceNumbers.size()) {
         return "Invalid index";
        }

        // Create a formatted string with the type and number
        string formattedType = resourceTypes[index] + "-" + to_string(resourceNumbers[index]);

        return formattedType;
    }

    // Method to determine the resource based on dice roll result
    string Tile::determineResourceByDiceRoll(int result) {
    // Iterate through the list of numbers associated with the tile
    for (size_t i = 0; i < resourceNumbers.size(); ++i) {
        // Check if the current number matches the dice roll result
        if (resourceNumbers[i] == static_cast<unsigned int>(result)) {
            // Return the corresponding resource type
            return resourceTypes[i];
         }
     }
        // Return a meaningful message if no matching number is found
        return "No resource found";
    }
    std::ostream& operator<<(std::ostream& os, Tile& t) {
        os << t.tileOwner << "("<<to_string(t.tileID)<<")" << "\033[0m" << "    ";
        return os;
    }
    bool Tile::operator==(Tile other) {
        return (*this).tileID == other.tileID; 
    }
    // Method to determine if two tiles are close to each other
    bool Tile::closeTo(Tile other) {
        for (auto neighbor : neighbors) {
            if (neighbor == other.tileID) {
                return true;
            }
        }
       return false;
    }
    
}
