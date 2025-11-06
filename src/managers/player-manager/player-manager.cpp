#include "player-manager.h"

PlayerManager::PlayerManager()
{
}

void PlayerManager::shuffle()
{
    for (auto index = 0; index < deckZone.size(); index++)
    {
        int newPosition = index + (rand() % (deckZone.size() - index));
        CardManager::Card hold = deckZone.at(newPosition);
        deckZone.at(newPosition) = deckZone.at(index);
        deckZone.at(index) = hold;
    }
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
    cardRef = CardManager::getInstance();

    masterDeck = {};
    deckZone = {};
    discardZone = {};
    handZone = {};
    focusZone = {};
}

void PlayerManager::shutDown()
{
}

void PlayerManager::addCardsToMasterDeck(std::vector<CardManager::CardName> cardsToAdd)
{
    for (auto card : cardsToAdd)
    {
        addCardToMasterDeck(card);
    }
}

void PlayerManager::addCardToMasterDeck(CardManager::CardName cardToAdd)
{
    masterDeck.push_back(cardRef->masterCardList.at(cardToAdd));
}

void PlayerManager::fightStart()
{
    deckZone = masterDeck;
    shuffle();
}

void PlayerManager::drawCard()
{
    // Reshuffle if deck is draw pile
    if (deckZone.empty())
    {
        deckZone = discardZone;
        discardZone = {};
        shuffle();
    }

    // If draw pile is still empty, player doesn't draw anymore cards
    if (deckZone.empty())
    {
        return;
    }
    handZone.push_back(deckZone.back());
    deckZone.pop_back();
}

void PlayerManager::drawCards(int num)
{
    for (int i = 0; i < num; i++)
    {
        drawCard();
    }
}

void PlayerManager::moveToDiscard()
{
    int initialSize = handZone.size();
    int removedCards = 0;
    for (int i = 0; i < initialSize; i++)
    {
        int targetIndex = i - removedCards;
        discardZone.push_back(handZone.at(targetIndex));
        handZone.erase(handZone.begin() + targetIndex);
        removedCards++;
    }
}
