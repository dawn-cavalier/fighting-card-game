#include "player-manager.h"

PlayerManager::PlayerManager()
{
}

PlayerManager *PlayerManager::getInstance()
{
    if (instancePtr == nullptr)
    {
        instancePtr = new PlayerManager();
    }
    return instancePtr;
}

PlayerManager::~PlayerManager()
{
}

void PlayerManager::startUp()
{
    masterDeck = {};
    deckZone = {};
    discardZone = {};
    handZone = {};
    focusZone = {};
}

void PlayerManager::shutDown()
{
}
