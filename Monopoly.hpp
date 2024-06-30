//aseelzatmy3@gmail.com
//324885417
#ifndef MONOPOLY_CARD_HPP
#define MONOPOLY_CARD_HPP

#include "developmentCard.hpp"

namespace ariel {

    class Monopoly : public developmentCard {
    public:
        Monopoly();
        void playCard(Player& p, Catan& c) override;
    };

}
#endif //MONOPOLY_CARD_HPP