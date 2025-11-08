#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_init.h>

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

static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;

CardManager *CardManager::instancePtr = nullptr;
PlayerManager *PlayerManager::instancePtr = nullptr;
GameStateManager *GameStateManager::instancePtr = nullptr;

int main(int argc, char* argv[])
{
    startUp();
    GameStateManager* gameStateRef = GameStateManager::getInstance();

    while (gameStateRef->processState());

    shutDown();
    return 0;
}

const void startUp()
{
    if (!SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS))
    {
        auto msg = SDL_GetError();
        std::cerr << msg << std::endl;
        SDL_ClearError();
    }
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

    SDL_Quit();
}