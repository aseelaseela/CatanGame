//aseelzatmy3@gmail.com
//324885417
#ifndef YEAROFPLENTY_CARD_HPP
#define YEAROFPLENTY_CARD_HPP

#include "developmentCard.hpp"

namespace ariel {

    class YearOfPlenty : public developmentCard {
    public:
        YearOfPlenty();
        void playCard(Player& p, Catan& c) override;
    };

}
#endif //YEAROFPLENTY_CARD_HPP