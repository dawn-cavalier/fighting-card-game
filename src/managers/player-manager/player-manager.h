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

public:
    std::vector<CardManager::Card> masterDeck;
    std::vector<CardManager::Card> deckZone;
    std::vector<CardManager::Card> discardZone;
    std::vector<CardManager::Card> handZone;
    std::vector<CardManager::Card> focusZone;

    static PlayerManager *getInstance();

    PlayerManager(const PlayerManager &other) = delete;
    ~PlayerManager();

    void startUp() override;
    void shutDown() override;
};
#endif