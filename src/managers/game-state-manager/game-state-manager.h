#ifndef FCARD_GAMESTATEMANAGER_H_
#define FCARD_GAMESTATEMANAGER_H_

#include "../manager/manager.h"
#include "../player-manager/player-manager.h"

class GameStateManager : public Manager
{
private:
    static GameStateManager *instancePtr;
    GameStateManager();

public:
    PlayerManager *playerRef;

    static GameStateManager *getInstance();

    GameStateManager(const GameStateManager &other) = delete;
    ~GameStateManager();

    void startUp() override;
    void shutDown() override;
};
#endif