//aseelzatmy3@gmail.com
//324885417
#ifndef ROADBUILDING_CARD_HPP
#define ROADBUILDING_CARD_HPP

#include "developmentCard.hpp"

namespace ariel {

    class RoadBuilding : public developmentCard {
    public:
        RoadBuilding();
        void playCard(Player& p, Catan& c) override;
    };

}
#endif //ROADBUILDING_CARD_HPP