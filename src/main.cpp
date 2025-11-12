#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_init.h>
#include <string>
#include <iostream>

#include "./managers/card-manager/card-manager.h"
#include "./managers/player-manager/player-manager.h"
#include "./managers/game-state-manager/game-state-manager.h"
#include "./managers/control-manager/control-manager.h"

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

const void printUnrecongizedInput(uint32_t event);

CardManager *CardManager::instancePtr = nullptr;
PlayerManager *PlayerManager::instancePtr = nullptr;
GameStateManager *GameStateManager::instancePtr = nullptr;
ControlManager* ControlManager::instancePtr = nullptr;

/* We will use this renderer to draw into this window every frame. */
static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;

/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[])
{
    SDL_SetAppMetadata("Fighting Card Game", "1.0", "com.proofofconcept.fighting-card-game");

    // What else do I need init-ed?
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer("Fighting Card Game", 640, 480, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    SDL_SetRenderLogicalPresentation(renderer, 640, 480, SDL_LOGICAL_PRESENTATION_LETTERBOX);

    startUp();

    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{   
    auto mousePos = ControlManager::getInstance()->getMousePosition();
    switch (event->type)
    {
    case SDL_EVENT_QUIT:
        return SDL_APP_SUCCESS;  /* end the program, reporting success to the OS. */
    case SDL_EVENT_MOUSE_MOTION:
        ControlManager::getInstance()->getMouseInfo();
        SDL_Log("(%.2f, %.2f)", mousePos.x, mousePos.y);
        break;
    default:
        printUnrecongizedInput(event->type);
        break;
    }
    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void* appstate)
{
    const double now = ((double)SDL_GetTicks()) / 1000.0;  /* convert from milliseconds to seconds. */
    /* choose the color for the frame we will draw. The sine wave trick makes it fade between colors smoothly. */
    const float red = (float)(0.5 + 0.5 * SDL_sin(now));
    const float green = (float)(0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 2 / 3));
    const float blue = (float)(0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 4 / 3));
    SDL_SetRenderDrawColorFloat(renderer, red, green, blue, SDL_ALPHA_OPAQUE_FLOAT);  /* new color, full alpha. */

    /* clear the window to the draw color. */
    SDL_RenderClear(renderer);

    /* put the newly-cleared rendering on the screen. */
    SDL_RenderPresent(renderer);

    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void* appstate, SDL_AppResult result)
{
    /* SDL will clean up the window/renderer for us. */
    shutDown();
}

//int main(int argc, char* argv[])
//{
//    startUp();
//    GameStateManager* gameStateRef = GameStateManager::getInstance();
//
//    while (gameStateRef->processState());
//
//    shutDown();
//    return 0;
//}

const void startUp()
{
    // TODO: Replace with SDL
    srand(time(0));
    
    CardManager::getInstance()->startUp();
    ControlManager::getInstance()->startUp();
    PlayerManager::getInstance()->startUp();
    GameStateManager::getInstance()->startUp();

}

const void shutDown()
{
    GameStateManager::getInstance()->shutDown();
    PlayerManager::getInstance()->shutDown();
    ControlManager::getInstance()->shutDown();
    CardManager::getInstance()->shutDown();

    SDL_Quit();
}

const void printUnrecongizedInput(uint32_t event)
{
    std::string message = "Unhandled Event: 0x";
    int base10 = static_cast<int>(event);
    std::string base16 = "";
    while (base10 > 0)
    {
        int temp = base10 % 16;
        base16.insert(0, std::to_string(temp));
        base10 = base10 / 16;
    }
    message.append(base16);
    SDL_Log(message.c_str());
}
