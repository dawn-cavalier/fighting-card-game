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
    masterCardList =
        {
            {Block, Card("Block", {0, 0, 1}, Blue, 0, 1, 0)},
            {Bash, Card("Bash", {1, 0, 1}, Blue, 2, 1, 0)},
            {Feint, Card("Feint", {0, 1, 0}, Green, 0, 0, 1)},
            {Punch, Card("Punch", {1, 0, 0}, Red, 1, 0, 0)},
            {BigPunch, Card("Big Punch", {2, 0, 0}, Red, 3, 0, 0)},
        };
}

const void CardManager::shutDown()
{
}