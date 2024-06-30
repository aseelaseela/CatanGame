//aseelzatmy3@gmail.com
//324885417
#include "VictoryPoint.hpp"
#include "player.hpp"  // Include Player class definition if not already included
#include <iostream>

namespace ariel {

    VictoryPoint::VictoryPoint() : developmentCard("VictoryPoint") {}

    void VictoryPoint::playCard(Player& p, Catan& c) {
        p.addPoint(); // Increment the player's victory points by 1
        std::cout << "You played the Victory Point card. Your victory points increased by 1." << std::endl;
    }

}
