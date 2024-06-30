//aseelzatmy3@gmail.com
//324885417
#include "Monopoly.hpp"
#include "catan.hpp"

namespace ariel {

    Monopoly::Monopoly() : developmentCard("Monopoly") {}
    void Monopoly::playCard(Player& p, Catan& c) {
        // Step 1: Prompt player to choose a resource
        std::string resourceChoice;
        std::cout << "Choose a resource to monopolize (wool, wood, rock, ore, grain): ";
        std::cin >> resourceChoice;

        // Step 2: Monopolize the chosen resource from other players
        if (resourceChoice == "wool" || resourceChoice == "wood" || resourceChoice == "rock" ||
            resourceChoice == "ore" || resourceChoice == "grain") {

            // Iterate through all players in the game (Catan)
            for (Player& otherPlayer : c.getPlayers()) {
                if (&otherPlayer != &p) {  // Exclude current player (p)
                    if (resourceChoice == "wool")
                    {
                        otherPlayer.addWool(-1);
                        p.addWool(1);
                    }
                    else if (resourceChoice == "grain")
                    {
                        otherPlayer.addGrain(-1);
                        p.addGrain(1);
                    }
                    else if (resourceChoice == "ore")
                    {
                        otherPlayer.addOre(-1);
                        p.addOre(1);
                    }
                    else if (resourceChoice == "wood")
                    {
                        otherPlayer.addWood(-1);
                        p.addWood(1);
                    }
                    else if (resourceChoice == "rock")
                    {
                        otherPlayer.addRock(-1);
                        p.addRock(1);
                    }
                }
            }
            p.addMonopoly(-1);
    }
    else std::cout << "Invalid resource choice. Please choose from wool, wood, rock, ore, or grain." << std::endl;
}
}