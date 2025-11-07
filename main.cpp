#include "./src/managers/card-manager/card-manager.h"
#include "./src/managers/player-manager/player-manager.h"
#include "./src/managers/game-state-manager/game-state-manager.h"
// TODO: These should be linked automatically but for some reason they are not
#include "./src/managers/card-manager/card-manager.cpp"
#include "./src/managers/player-manager/player-manager.cpp"
#include "./src/managers/game-state-manager/game-state-manager.cpp"

/**
 * @brief Intializes all Managers
 *
 */
const void startUp();

/**
 * @brief Cleans up all Managers
 *
 */
const void shutDown();

CardManager *CardManager::instancePtr = nullptr;
PlayerManager *PlayerManager::instancePtr = nullptr;
GameStateManager *GameStateManager::instancePtr = nullptr;

int main(int argCount, char *argVariables[])
{
    // TODO: Replace
    startUp();
    auto gameStateRef = GameStateManager::getInstance();

    while (gameStateRef->processState())
        ;

    return 0;
}

const void startUp()
{
    // TODO: Replace with SDL
    srand(time(0));

    CardManager::getInstance()->startUp();
    PlayerManager::getInstance()->startUp();
    GameStateManager::getInstance()->startUp();
}

const void shutDown()
{
    PlayerManager::getInstance()->shutDown();
    CardManager::getInstance()->shutDown();
}