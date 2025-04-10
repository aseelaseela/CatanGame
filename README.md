Below is a polished, Markdown-friendly README that you can copy and paste into your repository. Feel free to adjust or remove sections according to your needs!

---

# CatanGame
**Author:** [Aseel Ahmad](https://github.com/aseelaseela)

This project is a simplified implementation of the popular board game **Catan** in C++. It features a dynamically generated game board, resource and trade mechanics, development cards, and all essential elements needed to run a basic Catan-style game in a console environment.

---

## Table of Contents
1. [Overview](#overview)
2. [Key Features](#key-features)
3. [Classes and Architecture](#classes-and-architecture)
   - [Board (Catan Board)](#board-catan-board)
   - [Player](#player)
   - [developmentCard (Base Class)](#developmentcard-base-class)
     - [RoadBuilding](#roadbuilding)
     - [Monopoly](#monopoly)
     - [VictoryPoint](#victorypoint)
     - [YearOfPlenty](#yearofplenty)
     - [Knight](#knight)
   - [Tile](#tile)
   - [Catan (Game Manager)](#catan-game-manager)
4. [Demo (demo.cpp)](#demo-democpp)
5. [Test Suite (test.cpp)](#test-suite-testcpp)
6. [Build and Run](#build-and-run)
7. [License & Acknowledgments](#license--acknowledgments)

---

## Overview
This implementation of **Catan** allows three players to compete by collecting resources, building roads and settlements, upgrading to cities, trading (with each other or the bank), and using development cards to gain strategic advantages. The game proceeds in turns until one player meets the victory conditions.

The project codebase is organized into multiple classes, each responsible for a specific part of the game logic (e.g., board setup, player actions, development cards, etc.).

---

## Key Features
- **Dynamic Board Generation**  
  Hexagonal tiles with random resource assignments and numbers (2–12). Includes one desert tile.
- **Player Resource Management**  
  Players accumulate and spend resources (wood, rock, wool, ore, grain) for building and trading.
- **Development Cards**  
  Supports Knight, Monopoly, Year of Plenty, Road Building, and Victory Point cards.
- **Road and Settlement Building**  
  Players can build roads, place settlements, and upgrade settlements to cities.
- **Dice Rolls & Resource Allocation**  
  Dice rolls trigger resource production for matching tiles.
- **Trading**  
  Trade with the bank or other players, adhering to resource exchange rules.
- **Victory Condition**  
  Players gain Victory Points via settlements, cities, and special development cards.

---

## Classes and Architecture

### Board (Catan Board)
Manages the game board consisting of **hexagonal tiles** (`Tile` objects).  
- **Initialization**: Randomly arranges resource tiles (Wood, Grain, Rock, Ore, Wool) and one Desert tile, assigning dice numbers (2–12).  
- **Connectivity**: Tracks neighboring tiles for adjacency rules.  
- **Functionality**:  
  - Set/retrieve tile info  
  - Manage tile ownership  
  - Print a visual representation (tiles, resource types, roads)

### Player
Represents a **Catan** player, tracking their resources, development cards, settlements, cities, roads, and victory points.  
- **Resource Management**: Add/remove resources, discard half if over the limit, trade with bank/other players.  
- **Development Cards**: Knight, Monopoly, Year of Plenty, Road Building, Victory Point.  
- **Building and Upgrading**: Build roads/settlements, upgrade settlements to cities.  
- **Victory Points**: Track ongoing points to determine a winner.

**Key Methods**:
- `buildARoad()`, `buildASettlement()`, `upgradedCity()`
- `tradeWithPlayer()`, `tradeWithBank()`
- `discardHalfToBank()`
- `printPoints()`

### developmentCard (Base Class)
Base class for Catan’s development cards, each having a `playCard(Player &p, Catan &c)` method defining its effect.  
- **Constructor**: `developmentCard(string cardType)`
- **Destructor**: Virtual to ensure proper cleanup of derived cards
- **playCard(...)**: Pure virtual; overridden in derived classes

#### RoadBuilding
- **When played**: Player can place two roads immediately if they have sufficient resources.

#### Monopoly
- **When played**: The player chooses one resource type; all other players must give all of that resource to the player.

#### VictoryPoint
- **When played**: Immediately grants the player +1 victory point.

#### YearOfPlenty
- **When played**: Player chooses any one resource and gains two units of it.

#### Knight
- **When played**: Increases the player's knight count by one. Key for achieving the largest army bonus.

### Tile
Represents a **single tile** on the Catan board.  
- **Attributes**: Resource type, dice roll number, neighbors, roads, owner.  
- **Key Functions**:  
  - `getNeighboringTiles()`, `closeTo(...)`
  - `setOwner(...)`, `getOwner()`
  - `setRoadOwner(...)`, `getRoadOwner(...)`
  - `determineResourceByDiceRoll(...)`

### Catan (Game Manager)
Manages overall **game state** including players, the board, the deck of development cards, and turn progression.  
- **Players**: Stored in a vector.  
- **Board**: One `Board` object for the entire game.  
- **Development Cards**: A stack of `unique_ptr<developmentCard>` objects, randomly shuffled at game start.  
- **Gameplay Methods**:  
  - `chooseStartingPlayer()`, `rollDice()`, `nextTurn()`
  - `placeSettlement()`, `placeRoad()`, `upgradeSettlement()`
  - `trade()`, `buyDevelopmentCard()`, `useDevelopmentCard()`
  - `checkWinner()`, `enforceDiscardingRule()`
  - `printBoard()`

---

## Demo (demo.cpp)
A **demo** showcasing a simplified game flow:
1. Prompts three players for their names and assigns colors (orange, pink, green).
2. Each player places two settlements and two roads.
3. Players take turns rolling dice, building roads/settlements/cities, buying and using development cards, and trading.
4. Continues until one player meets the victory conditions.

---

## Test Suite (test.cpp)
Utilizes [**Doctest**](https://github.com/onqtam/doctest) to perform **unit tests** on:
- Player resource and trade operations  
- Board generation and tile adjacency  
- Correct usage and effects of development cards  
- Dice roll and resource distribution logic  
- Victory condition checks  

Tests employ **mock I/O** streams to simulate user interactions and verify both typical and edge-case scenarios.

---

## Build and Run
A **Makefile** is included for easy compilation and testing.

1. **Requirements**:
   - `clang++` (or another C++14-compliant compiler)
   - [Doctest header](https://github.com/onqtam/doctest) (included in the project)

2. **Clone the Repository**:
   ```bash
   git clone https://github.com/aseelaseela/CatanGame.git
   cd CatanGame
   ```

3. **Compile the Demo**:
   ```bash
   make demo
   ```
   This command compiles the main game executable (`demo`).

4. **Run the Game**:
   ```bash
   ./demo
   ```

5. **Compile and Run Tests**:
   ```bash
   make test
   ./test
   ```
   This command compiles and runs the test suite to verify core functionality.

6. **Clean Up**:
   ```bash
   make clean
   ```
   Removes compiled object files and executables.

---

## License & Acknowledgments
This project was created by **Aseel Ahmad** as a simplified C++ recreation of the board game *Settlers of Catan*. For details and further updates, visit the [GitHub repository](https://github.com/aseelaseela/CatanGame).  

*Note: The original *Settlers of Catan* board game is owned by Catan GmbH. This project is a fan-made educational example and is not affiliated with the official Catan franchise.*
