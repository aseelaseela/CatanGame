//aseelzatmy3@gmail.com
//324885417
#ifndef DEVELOPMENT_CARD_HPP
#define DEVELOPMENT_CARD_HPP

#include "player.hpp"
#include <iostream>
#include <string>
#include <memory>

namespace ariel {

    class Catan; 

    // Base class Devcard
    class developmentCard {
    private:
        string cardType;

    public:
        developmentCard(string cardType);
        virtual ~developmentCard();
        virtual void playCard(Player& p, Catan& c) = 0;  
    };

}
#endif //DEVELOPMENT_CARD_HPP