//aseelzatmy3@gmail.com
//324885417
#ifndef VICTORYPOINT_CARD_HPP
#define VICTORYPOINT_CARD_HPP
#include "developmentCard.hpp"

namespace ariel {

    class VictoryPoint : public developmentCard {
    public:
        VictoryPoint();
        void playCard(Player& p, Catan& c) override;
    };

}
#endif //VICTORYPOINT_CARD_HPP