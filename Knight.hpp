//aseelzatmy3@gmail.com
//324885417
#ifndef KNIGHT_CARD_HPP
#define KNIGHT_CARD_HPP
#include "developmentCard.hpp"

namespace ariel {

    class Knight : public developmentCard {
    public:
        Knight();
        void playCard(Player& p, Catan& c) override;
    };

}
#endif //KNIGHT_CARD_HPP