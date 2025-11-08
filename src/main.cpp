#include "./managers/card-manager/card-manager.h"
#include "./managers/player-manager/player-manager.h"
#include "./managers/game-state-manager/game-state-manager.h"

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

int main()
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