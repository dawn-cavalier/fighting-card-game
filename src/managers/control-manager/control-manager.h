#ifndef FCARD_CONTROLMANAGER_H_
#define FCARD_CONTROLMANAGER_H_
#include <SDL3/SDL_mouse.h>
#include <SDL3/SDL_keyboard.h>
#include <map>

// Used for printing, not necessary
#include <SDL3/SDL_log.h>

#include "../manager/manager.h"

struct MousePoint
{
    float x;
    float y;
    MousePoint(float x, float y) : x(x), y(y) {};
};

enum KeyboardGameCommands
{
    END_TURN,
    VIEW_DISCARD,
    VIEW_ACTIVE_DECK,
    VIEW_MASTER_DECK,
    CARD_0,
    CARD_1,
    CARD_2,
    CARD_3,
    CARD_4,
    CARD_5,
    CARD_6,
    CARD_7,
    CARD_8,
    CARD_9,
};

class ControlManager :
    public Manager
{
private:

    static ControlManager* instancePtr;
    int* numkeys = new int(0);
    const bool* keyState;

    std::map<KeyboardGameCommands, SDL_Scancode> keybinds = {
        {END_TURN, SDL_SCANCODE_RETURN},
        {VIEW_MASTER_DECK, SDL_SCANCODE_P},
        {VIEW_DISCARD, SDL_SCANCODE_D},
        {VIEW_ACTIVE_DECK, SDL_SCANCODE_Q},
        {CARD_0, SDL_SCANCODE_0},
        {CARD_1, SDL_SCANCODE_1},
        {CARD_2, SDL_SCANCODE_2},
        {CARD_3, SDL_SCANCODE_3},
        {CARD_4, SDL_SCANCODE_4},
        {CARD_5, SDL_SCANCODE_5},
        {CARD_6, SDL_SCANCODE_6},
        {CARD_7, SDL_SCANCODE_7},
        {CARD_8, SDL_SCANCODE_8},
        {CARD_9, SDL_SCANCODE_9},
    };

    ControlManager();
public:
    static ControlManager* getInstance();

    ControlManager(const ControlManager& other) = delete;
    ~ControlManager();

    void startUp() override;
    void shutDown() override;

    SDL_MouseButtonFlags getMouseButtons();
    MousePoint getMousePosition();

    bool getKeyboardCommandState(KeyboardGameCommands command);
};
#endif