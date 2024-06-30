//aseelzatmy3@gmail.com
//324885417
#include "RoadBuilding.hpp"
#include "catan.hpp"

namespace ariel {

    RoadBuilding::RoadBuilding() : developmentCard("RoadBuilding") {}

     void RoadBuilding::playCard(Player& p, Catan& c) {
        // Check if the player has at least 2 roads available
        if (p.getRoads() >= 14) {
            std::cout << "You have reached the maximum limit of roads." << std::endl;
            return;
        }

        std::cout << "You played the Road Building card." << std::endl;

        // Attempt to place the first road
        p.addWood(2);
        p.addRock(2);
        if (c.placeRoad(p))
        {
         std::cout << "First road placed successfully." << std::endl;
        // Attempt to place the second road
        p.addWood(2);
        p.addRock(2);
        p.buildARoad();
        }
        else std::cout << "Could not place the First road. Resources reverted." << std::endl;
        if (c.placeRoad(p))
        {
         std::cout << "Second road placed successfully." << std::endl;
        // Attempt to place the second road
        p.addWood(2);
        p.addRock(2);
        p.buildARoad();
        }
        else std::cout << "Could not place the Second road. Resources reverted." << std::endl;
        // Reduce the player's Road Building card count by 1
        p.addRoadBuilding(-1);
    }
}
