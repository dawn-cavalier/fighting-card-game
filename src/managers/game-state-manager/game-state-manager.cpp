#include "game-state-manager.h"

GameStateManager::GameStateManager()
{
}

GameStateManager *GameStateManager::getInstance()
{
    if (instancePtr == nullptr)
    {
        instancePtr = new GameStateManager();
    }
    return instancePtr;
}

GameStateManager::~GameStateManager()
{
}

void GameStateManager::startUp()
{
}

void GameStateManager::shutDown()
{
}
