#include "card-manager.h"
CardManager::CardManager()
{
}

CardManager *CardManager::getInstance()
{
    if (instancePtr == nullptr)
    {
        instancePtr = new CardManager();
    }
    return instancePtr;
}

CardManager::~CardManager()
{
}

const void CardManager::startUp()
{
}

const void CardManager::shutDown()
{
}