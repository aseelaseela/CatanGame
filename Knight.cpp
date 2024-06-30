//aseelzatmy3@gmail.com
//324885417
#include "Knight.hpp"

namespace ariel {

    Knight::Knight() : developmentCard("Knight") {}

    void Knight::playCard(Player& p, Catan& c) {
        p.addKnights(1);
        cout << "You played the Knight card. Knights increased by 1." << endl;
    }

}
