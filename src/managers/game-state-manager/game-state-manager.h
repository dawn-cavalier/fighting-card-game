#ifndef FCARD_GAMESTATEMANAGER_H_
#define FCARD_GAMESTATEMANAGER_H_

#include <string>
#include <iostream>

#include "../manager/manager.h"
#include "../player-manager/player-manager.h"
#include "../control-manager/control-manager.h"

class GameStateManager : public Manager
{
private:
    enum GameState
    {
        GameSetUp = 0,
        GameShutDown,
        FightStart,
        FightTurnStart,
        FightInhale,
        FightExhale,
        FightPlay,
        FightDiscard,
        FightTurnEnd
    };
    GameState state;

    static GameStateManager *instancePtr;
    GameStateManager();

    // TODO Move to input manager
    int pollUserInput(); 
    bool inhaleIteration();
    bool exhaleIteration();
    bool playIteration();

public:
    PlayerManager *playerRef;
    CardManager *cardRef;

    static GameStateManager *getInstance();

    GameStateManager(const GameStateManager &other) = delete;
    ~GameStateManager();

    void startUp() override;
    void shutDown() override;

    bool processState();
};
#endif