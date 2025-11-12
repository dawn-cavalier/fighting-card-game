#include "control-manager.h"

ControlManager::ControlManager() 
{
    mouseAbsoluteX = new float(0);
    mouseAbsoluteY = new float(0);
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
    mouseAbsoluteX = new float(0);
    mouseAbsoluteY = new float(0);
}

void ControlManager::shutDown()
{
}

void ControlManager::getMouseInfo()
{
    const SDL_MouseButtonFlags buttonFlags = SDL_GetMouseState(mouseAbsoluteX, mouseAbsoluteY);
}

MousePoint ControlManager::getMousePosition()
{
    return MousePoint(*mouseAbsoluteX, *mouseAbsoluteY);
}
