//aseelzatmy3@gmail.com
//324885417
#include "YearOfPlenty.hpp"

namespace ariel {

    YearOfPlenty::YearOfPlenty() : developmentCard("YearOfPlenty") {}

    void YearOfPlenty::playCard(Player& p, Catan& c) {
        std::cout << "Playing Year of Plenty card...\n";

        // List of resources to choose from
        std::vector<std::string> resources = {"Wood", "Rock", "Wool", "Ore", "Grain"};

        // Prompt the player to choose a resource
        std::cout << "Choose a resource to receive 2 units of:\n";
        for (size_t i = 0; i < resources.size(); ++i) {
            std::cout << i + 1 << ". " << resources[i] << "\n";
        }

        size_t choice;
        std::cout << "Enter your choice (1-5): ";
        std::cin >> choice;

        // Validate the choice
        if (choice < 1 || choice > resources.size()) {
            std::cout << "Invalid choice.\n";
            return;
        }

        // Adjust for zero-based index
        std::string selectedResource = resources[choice - 1];

        // Add 2 units of the selected resource to the player's inventory
        if (selectedResource == "Wood") {
            p.addWood(2);
        } else if (selectedResource == "Rock") {
            p.addRock(2);
        } else if (selectedResource == "Wool") {
            p.addWool(2);
        } else if (selectedResource == "ore") {
            p.addOre(2);
        } else if (selectedResource == "Grain") {
            p.addGrain(2);
        }

        // Reduce the player's YearOfPlenty card count by 1
        p.addYearOfPlenty(-1);

        std::cout << "You received 2 units of " << selectedResource << ".\n";
        std::cout << "Year of Plenty card count reduced to: " << p.getYearOfPlenty() << "\n";
    }

} // namespace ariel
