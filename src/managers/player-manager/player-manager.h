#ifndef FCARD_PLAYERMANAGER_H_
#define FCARD_PLAYERMANAGER_H_

#include <vector>

#include "../manager/manager.h"
#include "../card-manager/card-manager.h"

class PlayerManager : public Manager
{
private:
    static PlayerManager *instancePtr;
    PlayerManager();

    // Deck Zone
    void shuffle();
public:
    std::vector<CardManager::Card> masterDeck;
    std::vector<CardManager::Card> deckZone;
    std::vector<CardManager::Card> discardZone;
    std::vector<CardManager::Card> handZone;
    std::vector<CardManager::Card> focusZone;

    CardManager *cardRef;

    static PlayerManager *getInstance();

    PlayerManager(const PlayerManager &other) = delete;
    ~PlayerManager();

    void startUp() override;
    void shutDown() override;

    // Master Deck
    void addCardsToMasterDeck(std::vector<CardManager::CardName> cardsToAdd);
    void addCardToMasterDeck(CardManager::CardName cardToAdd);

    // Deck Zone
    void fightStart();

    // Hand Zone
    void drawCard();
    void drawCards(int num);
    void moveToDiscard();
};
#endif