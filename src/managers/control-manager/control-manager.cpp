#include "control-manager.h"

ControlManager::ControlManager() 
{
    keyState = SDL_GetKeyboardState(numkeys);
}

ControlManager* ControlManager::getInstance()
{
    if (instancePtr == nullptr)
    {
        instancePtr = new ControlManager();
    }
    return instancePtr;
}

ControlManager::~ControlManager()
{
}

void ControlManager::startUp()
{
}

void ControlManager::shutDown()
{
}

SDL_MouseButtonFlags ControlManager::getMouseButtons()
{
    return SDL_GetMouseState(nullptr, nullptr);
}

MousePoint ControlManager::getMousePosition()
{
    float* mouseAbsoluteX = new float(0);
    float* mouseAbsoluteY = new float(0);

    SDL_GetMouseState(mouseAbsoluteX, mouseAbsoluteY);
    return MousePoint(*mouseAbsoluteX, *mouseAbsoluteY);
}

bool ControlManager::getKeyboardCommandState(KeyboardGameCommands command)
{
    return keyState[keybinds.at(command)];
}
