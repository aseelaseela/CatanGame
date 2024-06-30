//aseelzatmy3@gmail.com
//324885417
// test.cpp
#include "doctest.h"
// Include headers for your classes to test
#include "catan.hpp"
#include "player.hpp"
#include "board.hpp"
#include "tile.hpp"
#include "Monopoly.hpp"
#include "Knight.hpp"
#include "RoadBuilding.hpp"
#include "VictoryPoint.hpp"
#include "YearOfPlenty.hpp"
#include "developmentCard.hpp"
#include <sstream>   
#include <algorithm> // For std::shuffle
#include <chrono> // For std::chrono::system_clock
#include <memory> // For std::unique_ptr
#include <random> // For std::default_random_engine
#include <vector> // For std::vector

using namespace std;
using namespace ariel;

TEST_CASE("Trade function test cases") {

    // Setup two players
    Player player1, player2;
    
    // Assign initial resources to player1 and player2
    player1.setResources(10, 10, 10, 10, 10);  // function to set resources directly for testing
    player2.setResources(5, 5, 5, 5, 5);
    
    // Mock input and output
    auto cin_buff = std::cin.rdbuf();
    auto cout_buff = std::cout.rdbuf();
    std::istringstream in;
    std::ostringstream out;
    std::cin.rdbuf(in.rdbuf());
    std::cout.rdbuf(out.rdbuf());

    SUBCASE("Successful trade") {
        in.str("1\n1\n1\n1\n1\n1\n1\n1\n1\n1\nyes\n"); // Mock user input for a successful trade
        
        // Execute trade
        bool result = player1.tradeWithPlayer(player2);
        
        // Check if the trade was successful
        CHECK(result == true);
        
        // Verify final resources
        CHECK(player1.getWool() == 10);
        CHECK(player1.getWood() == 10);
        CHECK(player1.getOre() == 10);
        CHECK(player1.getRock() == 10);
        CHECK(player1.getGrain() == 10);
        CHECK(player2.getWool() == 5);
        CHECK(player2.getWood() == 5);
        CHECK(player2.getOre() == 5);
        CHECK(player2.getRock() == 5);
        CHECK(player2.getGrain() == 5);
    }

    SUBCASE("Trade declined by other player") {
        in.str("1\n1\n1\n1\n1\n1\n1\n1\n1\n1\nno\n"); // Mock user input for a declined trade
        
        // Execute trade
        bool result = player1.tradeWithPlayer(player2);
        
        // Check if the trade was declined
        CHECK(result == false);
        
        // Verify resources remain unchanged
        CHECK(player1.getWool() == 10);
        CHECK(player1.getWood() == 10);
        CHECK(player1.getOre() == 10);
        CHECK(player1.getRock() == 10);
        CHECK(player1.getGrain() == 10);
        CHECK(player2.getWool() == 5);
        CHECK(player2.getWood() == 5);
        CHECK(player2.getOre() == 5);
        CHECK(player2.getRock() == 5);
        CHECK(player2.getGrain() == 5);
    }

    SUBCASE("Not enough resources to give by the current player") {
        in.str("11\n1\n1\n1\n1\n1\n1\n1\n1\n1\nyes\n"); // Mock user input for insufficient resources
        
        // Execute trade
        bool result = player1.tradeWithPlayer(player2);
        
        // Check if the trade failed due to insufficient resources
        CHECK(result == false);
        
        // Verify resources remain unchanged
        CHECK(player1.getWool() == 10);
        CHECK(player1.getWood() == 10);
        CHECK(player1.getOre() == 10);
        CHECK(player1.getRock() == 10);
        CHECK(player1.getGrain() == 10);
        CHECK(player2.getWool() == 5);
        CHECK(player2.getWood() == 5);
        CHECK(player2.getOre() == 5);
        CHECK(player2.getRock() == 5);
        CHECK(player2.getGrain() == 5);
    }

    SUBCASE("Not enough resources to receive by the other player") {
        in.str("1\n1\n1\n1\n1\n6\n6\n6\n6\n6\nyes\n"); // Mock user input for insufficient resources by the other player
        
        // Execute trade
        bool result = player1.tradeWithPlayer(player2);
        
        // Check if the trade failed due to insufficient resources by the other player
        CHECK(result == false);
        
        // Verify resources remain unchanged
        CHECK(player1.getWool() == 10);
        CHECK(player1.getWood() == 10);
        CHECK(player1.getOre() == 10);
        CHECK(player1.getRock() == 10);
        CHECK(player1.getGrain() == 10);
        CHECK(player2.getWool() == 5);
        CHECK(player2.getWood() == 5);
        CHECK(player2.getOre() == 5);
        CHECK(player2.getRock() == 5);
        CHECK(player2.getGrain() == 5);
    }
    SUBCASE("Player trying to trade with himself") {
        in.str("1\n1\n1\n1\n1\n1\n1\n1\n1\n1\nyes\n"); // This input shouldn't affect the test
        
        bool result = player1.tradeWithPlayer(player1);
        
        CHECK(result == false); // Ensure trade is declined
        
        // Verify resources remain unchanged
        CHECK(player1.getWool() == 10);
        CHECK(player1.getWood() == 10);
        CHECK(player1.getOre() == 10);
        CHECK(player1.getRock() == 10);
        CHECK(player1.getGrain() == 10);
        CHECK(player2.getWool() == 5);
        CHECK(player2.getWood() == 5);
        CHECK(player2.getOre() == 5);
        CHECK(player2.getRock() == 5);
        CHECK(player2.getGrain() == 5);
    }
    SUBCASE("Trading the same type of resource in both directions") {
        in.str("1\n0\n0\n0\n0\n1\n0\n0\n0\n0\nyes\n"); // Attempting to trade Wool in both directions
        
        bool result = player1.tradeWithPlayer(player2);
        
        CHECK(result == false); // Ensure trade is declined
        
        // Verify resources remain unchanged
        CHECK(player1.getWool() == 10);
        CHECK(player1.getWood() == 10);
        CHECK(player1.getOre() == 10);
        CHECK(player1.getRock() == 10);
        CHECK(player1.getGrain() == 10);
        CHECK(player2.getWool() == 5);
        CHECK(player2.getWood() == 5);
        CHECK(player2.getOre() == 5);
        CHECK(player2.getRock() == 5);
        CHECK(player2.getGrain() == 5);
    }
    // RestOre original cin and cout
    std::cin.rdbuf(cin_buff);
    std::cout.rdbuf(cout_buff);
}
TEST_CASE("Trade with bank function test cases") {

    // Setup a player
    Player player;
    
    // Assign initial resources to the player
    player.setResources(10, 10, 10, 10, 10);  // function to set resources directly for testing
    
    // Mock input and output
    auto cin_buff = std::cin.rdbuf();
    auto cout_buff = std::cout.rdbuf();
    std::istringstream in;
    std::ostringstream out;
    std::cin.rdbuf(in.rdbuf());
    std::cout.rdbuf(out.rdbuf());

    SUBCASE("Successful trade with bank") {
        in.str("4\n0\n0\n0\n0\n0\n1\n0\n0\n0\n"); // Mock user input for a successful trade
        
        // Execute trade with bank
        bool result = player.tradeWithBank();
        
        // Check if the trade was successful
        CHECK(result == true);
        
        // Verify final resources
        CHECK(player.getWool() == 6);
        CHECK(player.getWood() == 10);
        CHECK(player.getOre() == 10);
        CHECK(player.getRock() == 10);
        CHECK(player.getGrain() == 10);
        CHECK(player.getWool() == 6); // Received 1 Wool
    }

    SUBCASE("Not enough resources to give") {
        in.str("11\n0\n0\n0\n0\n0\n1\n0\n0\n0\n"); // Mock user input for insufficient resources
        
        // Execute trade with bank
        bool result = player.tradeWithBank();
        
        // Check if the trade failed due to insufficient resources
        CHECK(result == false);
        
        // Verify resources remain unchanged
        CHECK(player.getWool() == 10);
        CHECK(player.getWood() == 10);
        CHECK(player.getOre() == 10);
        CHECK(player.getRock() == 10);
        CHECK(player.getGrain() == 10);
    }

    SUBCASE("Give resources not divisible by 4") {
        in.str("5\n0\n0\n0\n0\n0\n1\n0\n0\n0\n"); // Mock user input for resources not divisible by 4
        
        // Execute trade with bank
        bool result = player.tradeWithBank();
        
        // Check if the trade failed due to incorrect resource amounts
        CHECK(result == false);
        
        // Verify resources remain unchanged
        CHECK(player.getWool() == 10);
        CHECK(player.getWood() == 10);
        CHECK(player.getOre() == 10);
        CHECK(player.getRock() == 10);
        CHECK(player.getGrain() == 10);
    }

    SUBCASE("Mismatched total give and receive") {
        in.str("4\n0\n0\n0\n0\n0\n0\n1\n0\n0\n"); // Mock user input for mismatched total resources
        
        // Execute trade with bank
        bool result = player.tradeWithBank();
        
        // Check if the trade failed due to mismatched total resources
        CHECK(result == false);
        
        // Verify resources remain unchanged
        CHECK(player.getWool() == 10);
        CHECK(player.getWood() == 10);
        CHECK(player.getOre() == 10);
        CHECK(player.getRock() == 10);
        CHECK(player.getGrain() == 10);
    }

    // RestOre original cin and cout
    std::cin.rdbuf(cin_buff);
    std::cout.rdbuf(cout_buff);
}
TEST_CASE("Player class test cases") {

    // Test default constructor
    SUBCASE("Default constructor") {
        Player player;
        
        CHECK(player.getName() == "");
        CHECK(player.getColor() == "");
        CHECK(player.getWood() == 4);
        CHECK(player.getRock() == 4);
        CHECK(player.getWool() == 2);
        CHECK(player.getOre() == 0);
        CHECK(player.getGrain() == 2);
        CHECK(player.getMonopoly() == 0);
        CHECK(player.getKnights() == 0);
        CHECK(player.getYearOfPlenty() == 0);
        CHECK(player.getRoadBuilding() == 0);
    }

    // Test parameterized constructor
    SUBCASE("Parameterized constructor") {
        Player player("Alice", "Red");
        
        CHECK(player.getName() == "Alice");
        CHECK(player.getColor() == "Red");
        CHECK(player.getWood() == 4);
        CHECK(player.getRock() == 4);
        CHECK(player.getWool() == 2);
        CHECK(player.getOre() == 0);
        CHECK(player.getGrain() == 2);
        CHECK(player.getMonopoly() == 0);
        CHECK(player.getKnights() == 0);
        CHECK(player.getYearOfPlenty() == 0);
        CHECK(player.getRoadBuilding() == 0);
    }

    // Test getters
    SUBCASE("Getters") {
        Player player("Bob", "Blue");

        // Set resources directly for testing purposes
        player.setResources(3, 5, 2, 4, 1);

        CHECK(player.getWood() == 5);
        CHECK(player.getRock() == 4);
        CHECK(player.getWool() == 3);
        CHECK(player.getOre() == 2);
        CHECK(player.getGrain() == 1);

        // Set development cards directly for testing purposes
        player.setDevelopmentCards(2, 3, 1, 4);

        CHECK(player.getMonopoly() == 2);
        CHECK(player.getKnights() == 3);
        CHECK(player.getYearOfPlenty() == 1);
        CHECK(player.getRoadBuilding() == 4);

        CHECK(player.getName() == "Bob");
        CHECK(player.getColor() == "Blue");
    }
}
TEST_CASE("Player class add resource and special card test cases") {
    
    Player player("Alice", "Red");
    
    // Test addWood method
    SUBCASE("Add wood") {
        player.addWood(3);
        CHECK(player.getWood() == 7);
        
        player.addWood(2);
        CHECK(player.getWood() == 9);
    }

    // Test addRock method
    SUBCASE("Add rock") {
        player.addRock(4);
        CHECK(player.getRock() == 8);
        
        player.addRock(1);
        CHECK(player.getRock() == 9);
    }

    // Test addWool method
    SUBCASE("Add wool") {
        player.addWool(2);
        CHECK(player.getWool() == 4);
        
        player.addWool(3);
        CHECK(player.getWool() == 7);
    }

    // Test addOre method
    SUBCASE("Add Ore") {
        player.addOre(1);
        CHECK(player.getOre() == 1);
        
        player.addOre(4);
        CHECK(player.getOre() == 5);
    }

    // Test addGrain method
    SUBCASE("Add Grain") {
        player.addGrain(5);
        CHECK(player.getGrain() == 7);
        
        player.addGrain(5);
        CHECK(player.getGrain() == 12);
    }

    // Test addPoint method
    SUBCASE("Add points") {
        player.addPoint();
        CHECK(player.getPoints() == 1);
        
        player.addPoint();
        CHECK(player.getPoints() == 2);
    }

    // Test addMonopoly method
    SUBCASE("Add monopoly") {
        player.addMonopoly(2);
        CHECK(player.getMonopoly() == 2);
        
        player.addMonopoly(1);
        CHECK(player.getMonopoly() == 3);
    }

    // Test addKnights method
    SUBCASE("Add knights") {
        player.addKnights(1);
        CHECK(player.getKnights() == 1);
        
        player.addKnights(2);
        CHECK(player.getKnights() == 3);
    }

    // Test addYearOfPlenty method
    SUBCASE("Add year of plenty") {
        player.addYearOfPlenty(3);
        CHECK(player.getYearOfPlenty() == 3);
        
        player.addYearOfPlenty(1);
        CHECK(player.getYearOfPlenty() == 4);
    }

    // Test addRoadBuilding method
    SUBCASE("Add road building") {
        player.addRoadBuilding(2);
        CHECK(player.getRoadBuilding() == 2);
        
        player.addRoadBuilding(2);
        CHECK(player.getRoadBuilding() == 4);
    }
}
TEST_CASE("Test Player::buildARoad") {
    Player player("Alice", "Red");
    player.setResources(30, 30, 30, 30, 30);

    // Build a single road
    player.buildARoad();
    CHECK(player.getWood() == 29);
    CHECK(player.getRock() == 29);
    CHECK(player.getRoads() == 1);

    // Build roads up to the limit
    player.setResources(30, 30, 30, 30, 30); // Reset resources
    for (int i = 1; i < 15; ++i) {
        player.buildARoad();
    }
    CHECK(player.getRoads() == 15);

    // Attempt to build the 16th road
    player.buildARoad();
    CHECK(player.getRoads() == 15);  // Should remain at 15
}
TEST_CASE("Test Player::buildASettlement") {
    Player player("Alice", "Red");
    player.setResources(30, 30, 30, 30, 30);

    // Build a single settlement
    player.buildASettlement();
    CHECK(player.getWood() == 29);
    CHECK(player.getWool() == 29);
    CHECK(player.getGrain() == 29);
    CHECK(player.getRock() == 29);
    CHECK(player.getsettlement() == 1);
    CHECK(player.getPoints() == 1);

    // Build settlements up to the limit
    player.setResources(30, 30, 30, 30, 30); // Reset resources
    for (int i = 1; i < 5; ++i) {
        player.buildASettlement();
    }
    CHECK(player.getsettlement() == 5);

    // Attempt to build the 6th settlement
    player.buildASettlement();
    CHECK(player.getsettlement() == 5);  // Should remain at 5
}
TEST_CASE("Test Player::upgradedCity") {
    Player player("Alice", "Red");
    player.setResources(30, 30, 30, 30, 30);

    // Upgrade a single city
    player.upgradedCity();
    CHECK(player.getOre() == 27);
    CHECK(player.getGrain() == 28);
    CHECK(player.getCity() == 1);
    CHECK(player.getPoints() == 1);

    // Upgrade cities up to the limit
    player.setResources(30, 30, 30, 30, 30); // Reset resources
    for (int i = 1; i < 4; ++i) {
        player.upgradedCity();
    }
    CHECK(player.getCity() == 4);

    // Attempt to upgrade the 5th city
    player.upgradedCity();
    CHECK(player.getCity() == 4);  // Should remain at 4
}
TEST_CASE("Test Player::printPoints") {
    Player player("Alice", "Red");

    std::ostringstream oss;
    std::streambuf* p_cout_streambuf = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());

    // Initial points
    player.printPoints();
    std::cout.rdbuf(p_cout_streambuf);
    CHECK(oss.str() == "Player Alice has 0 points.\n");

    // After adding points
    player.addPoint();
    player.addPoint();
    std::ostringstream oss2;
    std::cout.rdbuf(oss2.rdbuf());
    player.printPoints();
    std::cout.rdbuf(p_cout_streambuf);
    CHECK(oss2.str() == "Player Alice has 2 points.\n");
}

TEST_CASE("Test Player Equality Operators") {
    Player player1("Alice", "Red");
    Player player2("Alice", "Red");
    Player player3("Bob", "Blue");

    CHECK(player1 == player2);
    CHECK(player1 != player3);
}
TEST_CASE("Board constructor initializes tiles correctly") {
    Board board;

    // Use the getter method to access tiles
    const auto& tiles = board.getTilesboard();

    // Check the number of tiles initialized
    CHECK(tiles.size() == 54);

    // Check that each tile is initialized (assuming default constructor of Tile works correctly)
    for (const auto& tile : tiles) {
        CHECK(typeid(tile) == typeid(Tile));
    }
}
TEST_CASE("Board::getRoadColorBetweenTiles tests") {
    Board board;

    // Use the non-const getter to modify tiles
    auto& tiles = board.getMutableTiles();
    tiles[0].addInformation({"wood"}, {2}, {2}, 1);
    tiles[1].addInformation({"brick"}, {3}, {1, 3}, 2);
    tiles[0].setRoadOwner("Red", 0);

    // Test valid tiles with a connection
    //CHECK(board.getRoadColorBetweenTiles(1, 2, "Blue") == "RedBlue");

    // Test valid tiles without a connection
    CHECK(board.getRoadColorBetweenTiles(1, 3, "Blue") == "Blue");

    // Test out-of-bounds indices
    CHECK(board.getRoadColorBetweenTiles(0, 2, "Blue") == "Blue");
    CHECK(board.getRoadColorBetweenTiles(1, 55, "Blue") == "Blue");

    // Test edge cases
    tiles[0].addInformation({"wood"}, {2}, {2}, 1);
    tiles[53].addInformation({"ore"}, {8}, {52}, 54);
    //CHECK(board.getRoadColorBetweenTiles(54, 53, "Yellow") == "Yellow");
}

// Mock Player class for testing purposes
class MockPlayer : public Player {
public:
    // Implement necessary methods for testing, if applicable
};
// TEST_CASE("Catan constructor initializes correctly") {
//     // Create mock players
//     Player p1("Player1", "Red");
//     Player p2("Player2", "Blue");
//     Player p3("Player3", "Green");

//     // Create Catan object
//     ariel::Catan catan(p1, p2, p3);

//     // Check number of players
//     CHECK(catan.getPlayers().size() == 3);

//     // Check development card stack
//     CHECK(!catan.getDevCards().empty()); // Ensure devCards stack is not empty

//     // Count specific types of development cards
//     int victoryPointCount = 0;
//     int knightCount = 0;
//     int monopolyCount = 0;
//     int yearOfPlentyCount = 0;
//     int roadBuildingCount = 0;

//     // Iterate through the stack using top() and pop()
//     stack<unique_ptr<developmentCard>> tempStack = catan.getDevCards();

//     while (!tempStack.empty()) {
//         auto& card = tempStack.top();
//         if (dynamic_cast<VictoryPoint*>(card.get())) {
//             victoryPointCount++;
//         } else if (dynamic_cast<Knight*>(card.get())) {
//             knightCount++;
//         } else if (dynamic_cast<Monopoly*>(card.get())) {
//             monopolyCount++;
//         } else if (dynamic_cast<YearOfPlenty*>(card.get())) {
//             yearOfPlentyCount++;
//         } else if (dynamic_cast<RoadBuilding*>(card.get())) {
//             roadBuildingCount++;
//         }
//         tempStack.pop();
//     }

//     // Check counts of each type of development card
//     CHECK(victoryPointCount == 5);
//     CHECK(knightCount == 14);
//     CHECK(monopolyCount == 2);
//     CHECK(yearOfPlentyCount == 2);
//     CHECK(roadBuildingCount == 2);

//     // Additional checks if board initialization or other functionality is tested
//     // Example:
//     // CHECK(catan.getBoard().getNumTiles() == expectedNumTiles);
// }

TEST_CASE("Test chooseStartingPlayer function") {
    // Create some players for testing
    Player p1("Player1", "Red");
    Player p2("Player2", "Blue");
    Player p3("Player3", "Green");

    // Create a Catan game instance with these players
    Catan game(p1, p2, p3);

    // Test the function
    SUBCASE("Test player order after shuffling") {
        // Shuffle the players
        std::vector<Player>& shuffledPlayers = game.chooseStartingPlayer();

        // Check if the players vector is shuffled
        CHECK(shuffledPlayers.size() == 3);  // Assuming 3 players
        //CHECK(shuffledPlayers[0].getName() != "Player1");  // Check if different from original order
    }
}


TEST_CASE("Test nextTurn function") {
    // Create some players for testing
    Player p1("Player1", "Red");
    Player p2("Player2", "Blue");
    Player p3("Player3", "Green");

    // Create a Catan game instance with these players
    Catan game(p1, p2, p3);

    // Assume turn starts at 0 initially
    game.nextTurn();

    // Test the function
    CHECK(game.getCurrentPlayer().getName() == "Player2");  // Assuming getCurrentPlayer() returns the current player object
}
TEST_CASE("Roll Dice function test cases") {
    // Create an instance of your Catan class
    // Create some players for testing
    Player p1("Player1", "Red");
    Player p2("Player2", "Blue");
    Player p3("Player3", "Green");

    // Create a Catan game instance with these players
    Catan catan(p1, p2, p3);
    SUBCASE("Roll dice and check result") {
        // Call your rollDice function
        int sum = catan.rollDice();
        
        // Verify the outcome of the dice roll function
        CHECK(sum >= 2);
        CHECK(sum <= 12);
    }
}
TEST_CASE("Place Settlement function test cases") {
    // Create players
    Player p1("Player1", "Red");
    Player p2("Player2", "Blue");
    Player p3("Player3", "Green");

    // Create Catan game instance with these players
    Catan catan(p1, p2, p3);

    // Mock input and output streams
    std::istringstream in;
    std::ostringstream out;
    auto cin_buff = std::cin.rdbuf();
    auto cout_buff = std::cout.rdbuf();
    std::cin.rdbuf(in.rdbuf());
    std::cout.rdbuf(out.rdbuf());

    // Test scenarios

    // Successful placement scenario
    SUBCASE("Successful placement") {
        std::cout << "Testing successful placement...\n";
        in.str("1\n"); // Mock user input for spotIndex 1
        bool result = catan.placeSettlement(p1);
        CHECK(result == true);
    }

    // Not player's turn scenario
    SUBCASE("Not player's turn") {
        std::cout << "Testing not player's turn...\n";
        in.str("1\n"); // Mock user input for spotIndex 1
        bool result = catan.placeSettlement(p2); // Attempting to place with p2 when it's not their turn
        CHECK(result == false);
    }

    // Invalid spot index scenario
    SUBCASE("Invalid spot index") {
        std::cout << "Testing invalid spot index...\n";
        in.str("0\n1\n"); // Mock user input for invalid spotIndex 0 followed by valid spotIndex 1
        bool result = catan.placeSettlement(p1);
        CHECK(result == false);
    }

    // Restore original cin and cout
    std::cin.rdbuf(cin_buff);
    std::cout.rdbuf(cout_buff);
}
TEST_CASE("Upgrade Settlement function test cases") {
    // Create players
    Player p1("Player1", "Red");
    Player p2("Player2", "Blue");
    Player p3("Player3", "Green");

    // Create Catan game instance with these players
    Catan catan(p1, p2, p3);

    // Mock input and output streams
    std::istringstream in;
    std::ostringstream out;
    auto cin_buff = std::cin.rdbuf();
    auto cout_buff = std::cout.rdbuf();
    std::cin.rdbuf(in.rdbuf());
    std::cout.rdbuf(out.rdbuf());

    // Test scenarios

    // Successful upgrade scenario
    SUBCASE("Successful upgrade") {
        std::cout << "Testing successful upgrade...\n";

        // Player1's turn
        //catan.setCurrentPlayer(p1);
        catan.nextTurn(); // Move to Player2's turn
        catan.nextTurn(); // Move to Player3's turn
        catan.nextTurn(); // Move back to Player1's turn

        // Set the initial state: Player1 owns spot 1 with a settlement
        catan.getBoard().setOwner(1, "Red"); // Player1 owns spot 1 with a settlement

        // Mock user input for spotIndex 1
        in.str("1\n");

        bool result = catan.upgradeSettlement(p1);
        CHECK(result == true);

        // Verify output message if needed
         CHECK(out.str() == "Expected output message");
    }

    // Not player's turn scenario
    SUBCASE("Not player's turn") {
        std::cout << "Testing not player's turn...\n";

        // Player2's turn
        catan.setCurrentPlayer(1);

        // Set the initial state: Player1 owns spot 1 with a settlement
        catan.getBoard().setOwner(1, "Red"); // Player1 owns spot 1 with a settlement

        // Mock user input for spotIndex 1
        in.str("1\n");

        bool result = catan.upgradeSettlement(p1); // Attempting upgrade with Player1 when it's Player2's turn
        CHECK(result == false);

        // Verify output message if needed
         CHECK(out.str() == "Expected output message");
    }

    // Invalid spot index scenario
    SUBCASE("Invalid spot index") {
        std::cout << "Testing invalid spot index...\n";

        // Player1's turn
        catan.setCurrentPlayer(0);

        // Set the initial state: Player1 owns spot 1 with a settlement
        catan.getBoard().setOwner(1, "Red"); // Player1 owns spot 1 with a settlement

        // Mock user input for invalid spotIndex 0 followed by valid spotIndex 1
        in.str("0\n1\n");

        bool result = catan.upgradeSettlement(p1);
        CHECK(result == false);

        // Verify output message if needed
        CHECK(out.str() == "Expected output message");
    }

    // Spot not owned by the player scenario
    SUBCASE("Spot not owned by the player") {
        std::cout << "Testing spot not owned by the player...\n";

        // Player1's turn
        catan.setCurrentPlayer(0);

        // Set the initial state: Player2 owns spot 1 with a settlement
        catan.getBoard().setOwner(1, "Blue"); // Player2 owns spot 1 with a settlement

        // Mock user input for spotIndex 1
        in.str("1\n");

        bool result = catan.upgradeSettlement(p1); // Attempting upgrade with Player1 who doesn't own spot 1
        CHECK(result == false);

        // Verify output message if needed
        // CHECK(out.str() == "Expected output message");
    }

    // Restore original cin and cout
    std::cin.rdbuf(cin_buff);
    std::cout.rdbuf(cout_buff);
}

TEST_CASE("Place Road function test cases") {
    // Create players
    Player p1("Player1", "Red");
    Player p2("Player2", "Blue");
    Player p3("Player3", "Green");

    // Create Catan game instance with these players
    Catan catan(p1, p2, p3);

    // Mock input and output streams
    std::istringstream in;
    std::ostringstream out;
    auto cin_buff = std::cin.rdbuf();
    auto cout_buff = std::cout.rdbuf();
    std::cin.rdbuf(in.rdbuf());
    std::cout.rdbuf(out.rdbuf());

    // Test scenarios
    // Successful road placement scenario
    std::cout << "Testing successful road placement...\n";
    in.str("1\n2\n");
    bool result = catan.placeRoad(p1);
    CHECK(result == true);

    // Not player's turn scenario
    std::cout << "Testing not player's turn...\n";
    in.str("1\n2\n");
    result = catan.placeRoad(p2);
    CHECK(result == false);

    // Invalid spot indices scenario (0 is invalid)
    std::cout << "Testing invalid spot indices...\n";
    in.str("0\n2\n1\n0\n");
    result = catan.placeRoad(p1);
    CHECK(result == false);

    // Non-adjacent spots scenario
    std::cout << "Testing non-adjacent spots...\n";
    in.str("1\n3\n");
    result = catan.placeRoad(p1);
    CHECK(result == false);

    // Attempting to build road without connecting to existing road or settlement
    std::cout << "Testing not connecting to existing road or settlement...\n";
    in.str("1\n2\n");
    result = catan.placeRoad(p1);
    CHECK(result == false);

    // Restore original cin and cout
    std::cin.rdbuf(cin_buff);
    std::cout.rdbuf(cout_buff);
}
TEST_CASE("Check Winner function test cases") {
    // Create players
    Player p1("Player1", "Red");
    Player p2("Player2", "Blue");
    Player p3("Player3", "Green");

    // Create Catan game instance with these players
    Catan catan(p1, p2, p3);

    // Mock input and output streams
    std::istringstream in;
    std::ostringstream out;
    auto cin_buff = std::cin.rdbuf();
    auto cout_buff = std::cout.rdbuf();
    std::cin.rdbuf(in.rdbuf());
    std::cout.rdbuf(out.rdbuf());

    // Test scenarios
    // No clear leader in roads or knights
    std::cout << "Testing no clear leader in roads or knights...\n";
    p1.addRoads(3); // Player1 has 3 roads
    p2.addRoads(3); // Player2 also has 3 roads
    p3.addKnights(2); // Player3 has 2 knights
    bool result = catan.checkWinner();
    CHECK(result == false); // No bonus points should be awarded

    // Clear leader in roads
    std::cout << "Testing clear leader in roads...\n";
    p1.addRoads(5); // Player1 now has 5 roads
    p2.addRoads(4); // Player2 has 4 roads
    p3.addRoads(3); // Player3 has 3 roads
    result = catan.checkWinner();
    CHECK(result == true); // Bonus points should be awarded for most roads

    // Clear leader in knights
    std::cout << "Testing clear leader in knights...\n";
    p1.addKnights(4); // Player1 has 4 knights
    p2.addKnights(2); // Player2 has 2 knights
    p3.addKnights(4); // Player3 also has 4 knights
    result = catan.checkWinner();
    CHECK(result == true); // Bonus points should be awarded for most knights
        
    // Restore original cin and cout
    std::cin.rdbuf(cin_buff);
    std::cout.rdbuf(cout_buff);
}
TEST_CASE("Buy Development Card Function Tests") {
    // Mock input and output streams
    std::istringstream in;
    std::ostringstream out;
    auto cin_buff = std::cin.rdbuf();
    auto cout_buff = std::cout.rdbuf();
    std::cin.rdbuf(in.rdbuf());
    std::cout.rdbuf(out.rdbuf());

    // Create players
    Player p1("Player1", "Red");
    Player p2("Player2", "Blue");
    Player p3("Player3", "Green");

    // Create Catan game instance with these players
    Catan catan(p1, p2, p3);

    SUBCASE("Successful purchase of development card") {
        // Set up player resources
        p1.addGrain(1); // Ensure player has enough resources
        p1.addWool(1);
        p1.addOre(1);

        // Mock user input
        in.str(""); // Clear any existing input
        out.str(""); // Clear any existing output

        // Test buying a development card
        catan.buyDevelopmentCard(p1);

        // Check if the output indicates a successful purchase
        REQUIRE(out.str().find("You bought a ") != std::string::npos);
    }

    SUBCASE("Not player's turn") {
        // Set up player resources
        p1.addGrain(1); // Ensure player has enough resources
        p1.addWool(1);
        p1.addOre(1);

        // Set turn to another player
        // catan.setTurn(1); // Assuming you have a setTurn method

        // Mock user input
        in.str(""); // Clear any existing input
        out.str(""); // Clear any existing output

        // Test buying a development card
        catan.buyDevelopmentCard(p1);

        // Check if the output indicates it's not the player's turn
        REQUIRE(out.str().find("It's not your turn to buy a development card.") != std::string::npos);
    }

    SUBCASE("Insufficient resources") {
        // Player doesn't have enough resources
        p1.addGrain(0);
        p1.addWool(0);
        p1.addOre(0);

        // Mock user input
        in.str(""); // Clear any existing input
        out.str(""); // Clear any existing output

        // Test buying a development card
        catan.buyDevelopmentCard(p1);

        // Check if the output indicates insufficient resources
        REQUIRE(out.str().find("Insufficient resources to buy a development card.") != std::string::npos);
    }

    SUBCASE("No development cards available") {
        // Empty the development cards vector
        // catan.emptyDevCards(); // Assuming a method to empty devCards

        // Set up player resources
        p1.addGrain(1); // Ensure player has enough resources
        p1.addWool(1);
        p1.addOre(1);

        // Mock user input
        in.str(""); // Clear any existing input
        out.str(""); // Clear any existing output

        // Test buying a development card
        catan.buyDevelopmentCard(p1);

        // Check if the output indicates no development cards available
        REQUIRE(out.str().find("No development cards available.") != std::string::npos);
    }

    // Restore original cin and cout
    std::cin.rdbuf(cin_buff);
    std::cout.rdbuf(cout_buff);
}

TEST_CASE("Use Development Card Function Tests") {
    // Mock input and output streams
    std::istringstream in;
    std::ostringstream out;
    auto cin_buff = std::cin.rdbuf();
    auto cout_buff = std::cout.rdbuf();
    std::cin.rdbuf(in.rdbuf());
    std::cout.rdbuf(out.rdbuf());

    // Create players
    Player p1("Player1", "Red");
    Player p2("Player2", "Blue");
    Player p3("Player3", "Green");

    // Create Catan game instance with these players
    Catan catan(p1, p2, p3);

    SUBCASE("Using Knight Card") {
        p1.addKnights(1); // Give player a Knight card

        // Mock user input for choosing Knight card
        in.str("1\n");
        out.str(""); // Clear any existing output

        // Test using Knight card
        catan.useDevelopmentCard(p1);

        // Check if Knight card was used successfully
        REQUIRE(out.str().find("Development card used successfully.") != std::string::npos);
    }

    SUBCASE("Using Year of Plenty Card") {
        p1.addYearOfPlenty(1); // Give player a Year of Plenty card

        // Mock user input for choosing Year of Plenty card
        in.str("2\n");
        out.str(""); // Clear any existing output

        // Test using Year of Plenty card
        catan.useDevelopmentCard(p1);

        // Check if Year of Plenty card was used successfully
        REQUIRE(out.str().find("Development card used successfully.") != std::string::npos);
    }

    SUBCASE("Using Road Building Card") {
        p1.addRoadBuilding(1); // Give player a Road Building card

        // Mock user input for choosing Road Building card
        in.str("3\n");
        out.str(""); // Clear any existing output

        // Test using Road Building card
        catan.useDevelopmentCard(p1);

        // Check if Road Building card was used successfully
        REQUIRE(out.str().find("Development card used successfully.") != std::string::npos);
    }

    SUBCASE("Using Monopoly Card") {
        p1.addMonopoly(1); // Give player a Monopoly card

        // Mock user input for choosing Monopoly card
        in.str("4\n");
        out.str(""); // Clear any existing output

        // Test using Monopoly card
        catan.useDevelopmentCard(p1);

        // Check if Monopoly card was used successfully
        REQUIRE(out.str().find("Development card used successfully.") != std::string::npos);
    }

    SUBCASE("Invalid Choice") {
        // Mock user input for invalid choice
        in.str("5\n");
        out.str(""); // Clear any existing output

        // Test using an invalid choice
        catan.useDevelopmentCard(p1);

        // Check if the output indicates invalid choice
        REQUIRE(out.str().find("Invalid choice. No action taken.") != std::string::npos);
    }

    // Restore original cin and cout
    std::cin.rdbuf(cin_buff);
    std::cout.rdbuf(cout_buff);
}
TEST_CASE("Test Player::discardHalfToBank") {
    Player player("Alice", "Red");
    std::vector<int> resources = {4, 3, 2, 1, 5}; // wool, wood, ore, rock, grain
    player.setResources(resources[0], resources[1], resources[2], resources[3], resources[4]);

    SUBCASE("Discard exactly half of resources") {
        auto discarded = player.discardHalfToBank();

        CHECK(discarded.size() == 5);
        CHECK(discarded[0] + discarded[1] + discarded[2] + discarded[3] + discarded[4] == 7); // Total discarded should be half of 14 (sum of resources)
        CHECK(player.getWool() == resources[0] - discarded[0]);
        CHECK(player.getWood() == resources[1] - discarded[1]);
        CHECK(player.getOre() == resources[2] - discarded[2]);
        CHECK(player.getRock() == resources[3] - discarded[3]);
        CHECK(player.getGrain() == resources[4] - discarded[4]);
    }

    SUBCASE("Not enough resources to discard half") {
        // Set resources to a low amount
        player.setResources(1, 0, 0, 0, 0);
        auto discarded = player.discardHalfToBank();

        CHECK(discarded == std::vector<int>{0, 0, 0, 0, 0}); // No resources should be discarded
        CHECK(player.getWool() == 1);
        CHECK(player.getWood() == 0);
        CHECK(player.getOre() == 0);
        CHECK(player.getRock() == 0);
        CHECK(player.getGrain() == 0);
    }

    SUBCASE("More than enough resources to discard half") {
        // Set resources to a high amount
        player.setResources(10, 8, 6, 4, 12);
        auto discarded = player.discardHalfToBank();

        CHECK(discarded.size() == 5);
        CHECK(discarded[0] + discarded[1] + discarded[2] + discarded[3] + discarded[4] == 14); // Total discarded should be half of 28 (sum of resources)
        CHECK(player.getWool() == 10 - discarded[0]);
        CHECK(player.getWood() == 8 - discarded[1]);
        CHECK(player.getOre() == 6 - discarded[2]);
        CHECK(player.getRock() == 4 - discarded[3]);
        CHECK(player.getGrain() == 12 - discarded[4]);
    }

    SUBCASE("Edge case: No resources to discard") {
        // Set all resources to zero
        player.setResources(0, 0, 0, 0, 0);
        auto discarded = player.discardHalfToBank();

        CHECK(discarded == std::vector<int>{0, 0, 0, 0, 0}); // No resources should be discarded
        CHECK(player.getWool() == 0);
        CHECK(player.getWood() == 0);
        CHECK(player.getOre() == 0);
        CHECK(player.getRock() == 0);
        CHECK(player.getGrain() == 0);
    }
}