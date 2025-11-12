#ifndef FCARD_CONTROLMANAGER_H_
#define FCARD_CONTROLMANAGER_H_
#include <SDL3/SDL_mouse.h>

#include "../manager/manager.h"

struct MousePoint
{
    float x;
    float y;
    MousePoint(float x, float y) : x(x), y(y) {};
};

class ControlManager :
    public Manager
{
private:
    static ControlManager* instancePtr;

    float* mouseAbsoluteX;
    float* mouseAbsoluteY;

    ControlManager();
public:
    static ControlManager* getInstance();

    ControlManager(const ControlManager& other) = delete;
    ~ControlManager();

    void startUp() override;
    void shutDown() override;

    void getMouseInfo();
    MousePoint getMousePosition();
};

#endif